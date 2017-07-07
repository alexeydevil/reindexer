#pragma once

#include <string>

using namespace std;
namespace reindexer {

enum { errOK = 0, errParseSQL, errQueryExec, errParams, errLogic };

class Error {
public:
	Error(int code = errOK);
	Error(int code, const char *fmt, ...);

	const string &what() const;
	int code() const;
	bool ok() const { return code_ == errOK; }

protected:
	int code_;
	string what_;
};

#ifdef NDEBUG
#define assertf(...) ((void)0)
#else
#define assertf(e, fmt, ...)                                                                         \
	if (!(e)) {                                                                                      \
		fprintf(stderr, "%s:%d: failed assertion '%s':\n" fmt, __FILE__, __LINE__, #e, __VA_ARGS__); \
		abort();                                                                                     \
	}
#endif

}  // namespace reindexer
