#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const auto YES = "YES";
const auto NO = "NO";
const auto GENERIC_WORD_PATTERN = "[a-zA-Z]+";

int test_count;

vector<string> read_answer(InStream &stream) {
    vector<string> res;
    for (int i = 1; i <= test_count; ++i) {
        setTestCase(i);
        auto token = upperCase(stream.readToken(GENERIC_WORD_PATTERN, "token"));
        stream.quitif(token != YES && token != NO, _pe,
                      "Expected YES or NO token, but found \"%s\"",
                      token.c_str());
        res.push_back(token);
    }
    stream.quitif(!stream.seekEof(), _pe, "Expected EOF after reading %d token(s)",
                  test_count);

    return res;
}

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    test_count = inf.readInt();

    auto out_tokens = read_answer(ouf);
    auto ans_tokens = read_answer(ans);

    for (int i = 1; i <= test_count; ++i) {
        setTestCase(i);
        if (out_tokens[i - 1] != ans_tokens[i - 1]) {
            quitf(_wa, "expected %s, found %s", ans_tokens[i - 1].c_str(),
                  out_tokens[i - 1].c_str());
        }
    }

    quitf(_ok, "%d token(s)", test_count);

    return 0;
}
