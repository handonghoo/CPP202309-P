    #include <iostream>
    #include <string>
    #include <locale>

    using namespace std;

    // 문자열이 한국어인지 판별하는 함수
    bool isKorean(std::wstring& text) {
        wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> conv;
        string utf8_text = conv.to_bytes(text); // UTF-8로 변환된 문자열 획득

        // 한국어 유니코드 범위인 가 ~ 힣 사이의 문자가 포함되어 있는지 확인
        for (char c : utf8_text) {
            if (c >= -64 && c <= -19) {
                return true;
            }
        }
        return false;
    }

    // 문자열이 일본어인지 판별하는 함수
    bool isJapanese(std::wstring& text) {
        wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> conv;
        string utf8_text = conv.to_bytes(text); // UTF-8로 변환된 문자열 획득

        // 일본어 유니코드 범위인 ぁ ~ ん, ァ ~ ン, 一 ~ 龯 사이의 문자가 포함되어 있는지 확인
        for (char c : utf8_text) {
            if (c >= -29 && c <= -28) {
                return true;
            }
            else if (c >= -61 && c <= -16) {
                return true;
            }
            else if (c >= -27 && c <= -22) {
                return true;
            }
        }
        return false;
    }

    // 문자열이 영어인지 판별하는 함수
    bool isEnglish(std::wstring& text) {
        wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> conv;
        string utf8_text = conv.to_bytes(text); // UTF-8로 변환된 문자열 획득

        // 영어 알파벳이 포함되어 있는지 확인
        for (char c : utf8_text) {
            if (isalpha(c)) {
                return true;
            }
        }
        return false;
    }

    // 문자열이 중국어인지 판별하는 함수
    bool isChinese(std::wstring& text) {
        wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> conv;
        string utf8_text = conv.to_bytes(text); // UTF-8로 변환된 문자열 획득

        // 중국어 유니코드 범위인 4E00 ~ 9FFF 사이의 문자가 포함되어 있는지 확인
        for (char c : utf8_text) {
            if (c >= -30 && c <= -29) {
                return true;
            }
            else if (c >= -28 && c <= -27) {
                return true;
            }
        }
        return false;
    }

    int main() {
        std::locale::global(std::locale("")); // 현재 환경의 로케일을 사용하여 유니코드 문자열을 처리하도록 설정

        std::wstring text;
        std::wcout << "문자열을 입력하세요: ";
        std::getline(std::wcin, text);

        // UTF-8 인코딩으로 변환된 문자열을 얻습니다.
        std::string utf8_text = wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().to_bytes(text);

        // UTF-8 인코딩으로 변환된 문자열을 `std::cout`을 사용하여 출력합니다.
        std::cout << utf8_text;


       
        std::wcout << "문자열을 입력하세요: ";
        std::getline(std::wcin, text);

        if (isKorean(text)) {
            std::wcout << "입력된 문자열은 한국어입니다." << std::endl;
        }
        else if (isJapanese(text)) {
            std::wcout << "입력된 문자열은 일본어입니다." << std::endl;
        }
        else if (isEnglish(text)) {
            std::wcout << "입력된 문자열은 영어입니다." << std::endl;
        }
        else if (isChinese(text)) {
            std::wcout << "입력된 문자열은 중국어입니다." << std::endl;
        }
        else {
            std::wcout << "입력된 문자열은 한국어, 일본어, 영어, 중국어가 아닙니다." << std::endl;
        }

        return 0;
    }