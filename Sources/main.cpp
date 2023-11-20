#include <iostream>
#include <string>
#include <regex>

using namespace std;

bool isKorean(const wstring& text) {
    wregex regex(L"^[가-힣]+$");
    return regex_match(text, regex);
}

bool isChinese(const wstring& text) {
    wregex regex(L"^[\\u4E00-\\u9FFF]+$");
    return regex_match(text, regex);
}

bool isJapanese(const wstring& text) {
    wregex regex(L"^[ぁ-んァ-ン一-龯]+$");
    return regex_match(text, regex);
}

int main() {
    wstring text;
    wcout << "문자열을 입력하세요: ";
    getline(wcin, text);

    if (isKorean(text)) {
        wcout << "입력된 문자열은 한국어입니다." << endl;
    }
    else if (isChinese(text)) {
        wcout << "입력된 문자열은 중국어입니다." << endl;
    }
    else if (isJapanese(text)) {
        wcout << "입력된 문자열은 일본어입니다." << endl;
    }
    else {
        wcout << "입력된 문자열은 한국어, 중국어, 일본어가 아닙니다." << endl;
    }

    return 0;
}
