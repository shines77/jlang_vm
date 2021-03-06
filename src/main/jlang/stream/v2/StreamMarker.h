
#ifndef JLANG_STREAM_STREAMMARKER_H
#define JLANG_STREAM_STREAMMARKER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "jlang/stream/InputStringStream.h"
#include "jlang/stream/OutputStringStream.h"
#include "jlang/stream/StringStream.h"
#include "jlang/stream/MemoryStream.h"
#include "jlang/support/StringUtils.h"

#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#define REF_CAST_TO(value, toType) \
    (*(static_cast<toType *>(&value)))

namespace jlang {

///////////////////////////////////////////////////
// class StreamMarker
///////////////////////////////////////////////////

class StreamMarker {
private:
    StreamRoot & stream_;
    char * marker_;
#if !defined(NDEBUG) || defined(_DEBUG)
    bool marked_;
#endif

public:
    StreamMarker(StringStream & steam)
        : stream_(REF_CAST_TO(steam, StreamRoot)), marker_(nullptr)
#if !defined(NDEBUG) || defined(_DEBUG)
        , marked_(false)
#endif
    {
        /* Do nothing!! */
    }

    StreamMarker(InputStringStream & steam)
        : stream_(REF_CAST_TO(steam, StreamRoot)), marker_(nullptr)
#if !defined(NDEBUG) || defined(_DEBUG)
        , marked_(false)
#endif
    {
        /* Do nothing!! */
    }

    StreamMarker(OutputStringStream & steam)
        : stream_(REF_CAST_TO(steam, StreamRoot)), marker_(nullptr)
#if !defined(NDEBUG) || defined(_DEBUG)
        , marked_(false)
#endif
    {
        /* Do nothing!! */
    }

    StreamMarker(MemoryStream & steam)
        : stream_(REF_CAST_TO(steam, StreamRoot)), marker_(nullptr)
#if !defined(NDEBUG) || defined(_DEBUG)
        , marked_(false)
#endif
    {
        /* Do nothing!! */
    }
    ~StreamMarker() {}

    StreamRoot & get_stream() { return stream_; }
    const StreamRoot & get_stream() const { return stream_; }

    char * marker() const { return this->marker_; }
    char * current() const { return this->stream_.current(); }

#if !defined(NDEBUG) || defined(_DEBUG)
    bool has_marked() const { return ((marker_ != nullptr) && this->marked_); }
#else
    bool has_marked() const { return (marker_ != nullptr); }
#endif

    bool is_valid() const {
        return (stream_.is_valid()
            && (this->marker_ >= this->stream_.head())
            && (this->marker_ <= this->stream_.tail()));
    }

    char * start() const {
        assert(this->marker_ != nullptr);
        assert(this->has_marked());
        assert(this->marker_ >= this->stream_.head());
        return (this->marker_);
    }

    char * end() const {
        assert(this->marker_ != nullptr);
        assert(this->has_marked());
        return this->stream_.current();
    }

    intptr_t start_pos() const {
        assert(this->marker_ != nullptr);
        assert(this->has_marked());
        assert(this->marker_ >= this->stream_.head());
        return (this->marker_ - this->stream_.head());
    }

    intptr_t end_pos() const {
        assert(this->marker_ != nullptr);
        assert(this->has_marked());
        return (this->stream_.current() - this->stream_.head());
    }

    intptr_t length() const {
        assert(this->marker_ != nullptr);
        assert(this->has_marked());
        assert(this->stream_.current() >= this->marker_);
        return (this->stream_.current() - this->marker_);
    }

    char * get_marker() const { return this->start(); }
    char * get_current() const { return this->end(); }

    void set_current(char * position) {
        assert(position >= this->stream_.head() || position < this->stream_.tail());
        assert(position != nullptr);
        this->stream_.set_current(position);
    }

    void reset() {
        this->marker_ = nullptr;
#if !defined(NDEBUG) || defined(_DEBUG)
        this->marked_ = false;
#endif
    }

    void remark() {
        this->marker_ = this->stream_.current();
#if !defined(NDEBUG) || defined(_DEBUG)
        this->marked_ = true;
#endif
    }

    void set_mark(int offset = 0) {
#if !defined(NDEBUG) || defined(_DEBUG)
        if (!(this->marked_)) {
#else
        if (true) {
#endif
            this->marker_ = this->stream_.current() + offset;
#if !defined(NDEBUG) || defined(_DEBUG)
            this->marked_ = true;
#endif
        }
        else {
            throw("StreamMarker<T>:set_mark(), Error: can not be set the mark two times continuous.");
        }
    }

    void restore() {
#if !defined(NDEBUG) || defined(_DEBUG)
        if (this->marked_) {
#else
        if (true) {
#endif
            assert(this->marker_ >= this->stream_.head() || this->marker_ < this->stream_.tail());
            assert(this->marker_ != nullptr);
            this->stream_.set_current(marker_);
            this->marker_ = nullptr;
#if !defined(NDEBUG) || defined(_DEBUG)
            this->marked_ = false;
#endif
        }
        else {
            throw("StreamMarker<T>:restore(), Error: have no set the mark yet, can not be restore.");
        }
    }

    intptr_t copy_string(char * substr, size_t size) {
        assert(substr != nullptr);
        assert(this->end() >= this->start());
        if (likely(this->has_marked())) {
            return StringUtils::sub_str(substr, size, this->start(), this->end());
        }
        else {
            *substr = '\0';
            return 0;
        }
    }

    template <size_t N>
    intptr_t copy_string(char (&substr)[N]) {
        return this->copy_string(substr, N);
    }

    intptr_t copy_string(std::string & substr) {
        if (likely(this->has_marked())) {
            return StringUtils::sub_str(substr, this->start(), this->end());
        }
        else {
            substr.clear();
            return 0;
        }
    }

    intptr_t append_string(std::string & substr) {
        if (likely(this->has_marked())) {
            return StringUtils::append(substr, this->start(), this->end());
        }
        else {
            substr.clear();
            return 0;
        }
    }
};

} // namespace jlang

#endif // JLANG_STREAM_STREAMMARKER_H
