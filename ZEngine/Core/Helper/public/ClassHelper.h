#pragma once

#define CTR_CP_DEL(X) X(const X&) = delete;

#define CTR_MV_DEL(X) X(X&&) = delete;

#define OP_ASSIGN_CP_DEL(X) X& operator=(const X&) = delete;
