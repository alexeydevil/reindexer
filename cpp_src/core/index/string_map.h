#pragma once

#include <unordered_map>
#include "core/keyvalue/key_string.h"
#include "cpp-btree/btree_map.h"
#include "estl/intrusive_ptr.h"
#include "tools/customhash.h"
#include "tools/customlocal.h"
#include "tools/errors.h"
#include "tools/stringstools.h"

namespace reindexer {

using btree::btree_map;
using std::min;
using std::stoi;
using std::to_string;
using std::tolower;
using std::unordered_map;

struct comparator_sptr {
	explicit comparator_sptr() : collateMode_() {}
	comparator_sptr(const int collateMode) : collateMode_(collateMode) {}
	bool operator()(const key_string& lhs, const key_string& rhs) const {
		return collateCompare(Slice(*lhs), Slice(*rhs), collateMode_) < 0;
	}
	int collateMode_ = CollateNone;
};  // namespace reindexer

struct equal_sptr {
	explicit equal_sptr() : collateMode_() {}
	equal_sptr(const int collateMode) : collateMode_(collateMode) {}
	bool operator()(const key_string& lhs, const key_string& rhs) const {
		return collateCompare(Slice(*lhs), Slice(*rhs), collateMode_) == 0;
	}
	int collateMode_ = CollateNone;
};
struct hash_sptr {
	explicit hash_sptr() : collateMode_() {}
	hash_sptr(const int collateMode) : collateMode_(collateMode) {}
	size_t operator()(const key_string& s) const {
		if (collateMode_ == CollateUTF8) {
			wstring u16str;

			utf8_to_utf16(*s, u16str);
			ToLower(u16str);

			return std::hash<std::wstring>()(u16str);
		} else if (collateMode_ == CollateASCII) {
			return static_cast<size_t>(Hash(*s, true));
		}

		return std::hash<std::string>()(*s);
	}
	int collateMode_ = CollateNone;
};

template <typename T1>
using unordered_str_map = unordered_map<key_string, T1, hash_sptr, equal_sptr>;
template <typename T1>
using str_map = btree_map<key_string, T1, comparator_sptr>;

template <typename T>
struct is_string_unord_map_key : std::false_type {};
template <typename T1>
struct is_string_unord_map_key<unordered_str_map<T1>> : std::true_type {};
template <typename T>
struct is_string_map_key : std::false_type {};
template <typename T1>
struct is_string_map_key<str_map<T1>> : std::true_type {};

}  // namespace reindexer
