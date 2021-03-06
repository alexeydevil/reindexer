#pragma once
#include <string>
#include <vector>
#include "core/type_consts.h"

namespace reindexer {
using std::string;
using std::vector;

// Type of field
class PayloadFieldType {
public:
	PayloadFieldType(KeyValueType t, const string &n, const string &j, bool a)
		: type_(t), name_(n), jsonPaths_({j}), offset_(0), isArray_(a) {}

	size_t Sizeof() const;
	size_t ElemSizeof() const;
	size_t Alignof() const;
	bool IsArray() const { return isArray_; };
	void SetArray() { isArray_ = true; };
	void SetOffset(size_t o) { offset_ = o; }
	size_t Offset() const { return offset_; }
	KeyValueType Type() const { return type_; }
	const string &Name() const { return name_; }
	const vector<string> &JsonPaths() const { return jsonPaths_; }
	void AddJsonPath(const string &jsonPath) { jsonPaths_.push_back(jsonPath); }

protected:
	KeyValueType type_;
	string name_;
	vector<string> jsonPaths_;
	size_t offset_;
	bool isArray_;
};

}  // namespace reindexer
