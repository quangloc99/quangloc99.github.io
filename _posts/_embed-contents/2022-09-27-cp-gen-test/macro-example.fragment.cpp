#define MY_MACRO  // định nghĩa macro tên là MY_MACRO

int main() {
#ifdef MY_MACRO
    cout << "MY_MACRO exists" << endl;
#else 
    cout << "MY_MACRO does not exist" << endl;
#endif
    return 0;
}
