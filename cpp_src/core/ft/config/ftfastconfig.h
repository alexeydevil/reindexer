#pragma once

#include "baseconfig.h"

namespace reindexer {

using std::vector;
using std::string;

struct FtFastConfig : public BaseFTConfig {
	virtual void parse(char *json) final;

	double bm25Boost = 1.0;
	double bm25Weight = 0.5;
	double distanceBoost = 1.0;
	double distanceWeight = 0.5;
	double termLenBoost = 1.0;
	double termLenWeight = 0.3;
	double minRelevancy = 0.05;

	int maxTyposInWord = 1;
	int maxTypoLen = 15;
};

}  // namespace reindexer
