
#ifndef __JLANG_H__
#define __JLANG_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "jlang/basic/stddef.h"
#include "jlang/basic/coredef.h"
#include "jlang/basic/ValueType.h"
#include "jlang/asm/KeywordKind.h"
#include "jlang/asm/Keyword.h"
#include "jlang/asm/Token.h"
#include "jlang/lang/Global.h"
#include "jlang/system/System.h"
#include "jlang/vm/Interpreter_v1.h"
#include "jlang/vm/Interpreter_v2.h"
#include "jlang/vm/Interpreter_v3.h"
#include "jlang/vm/Interpreter_v4.h"

#include "jlang/asm/Parser.h"
#include "jlang/asm/Assembler.h"

#include "jlang/support/StopWatch.h"

#include "jlang/test/Assert.h"

#endif // __JLANG_H__
