# EduLanguage

## Chanpter 7

파일 스트림은 기본적인 istream 이나 ostream 클래스 보다 더 지원하는 기능이 더 많기 때문에 이를 상속 받아서 작성되었으며, 각각을 상속 받은 것이 ifstream 과 ofstream 입니다. 이들 클래스를 모두 포함하는 라이브러리로 fstream을 사용하면 됩니다.

ios_base에서 파생되어 순차적으로 ios, istream, iostream을 상속받는 fstream이 있으며 가장 기능이 많은 클래스이다.

```
// 파일에서의 입출력#include <fstream>#include <iostream>#include <string>


int main() {
  // 파일 읽기 준비
  std::ifstream in("test.txt");
  std::string s;


  if (in.is_open()) {
    in >> s;
    std::cout << "입력 받은 문자열 :: " << s << std::endl;
  } else {
    std::cout << "파일을 찾을 수 없습니다!" << std::endl;
  }
  return 0;
}

```


 - 파일을 읽어서 모두 스트링 객체로 전달 할 수 있다. ( in >> s)
 - ifstream 객체로 파일 명을 넣었는데 같은 위치에 있는 파일명을 찾는다.



```
// 이진수로 읽기#include <fstream>#include <iostream>#include <string>


int main() {
  // 파일 읽기 준비
  std::ifstream in("test.txt", std::ios::binary);
  std::string s;


  int x;
  if (in.is_open()) {
    in.read((char*)(&x), 4);
    std::cout << std::hex << x << std::endl;
  } else {
    std::cout << "파일을 찾을 수 없습니다!" << std::endl;
  }


  return 0;
}

```


- 방금전과 다르게 데이터를 이진수로 읽어 헥사 데이터로 출력했다.
- 이진수로 읽기 위해서 std::binary 라는 옵션값을 넣어줘야 하는데 이를 더해줌으로 여러가지 조합이 가능하다.



## 파일 전체 읽기

```
#include <fstream>
#include <iostream>#include <string>


int main() {
  // 파일 읽기 준비
  std::ifstream in("test.txt");
  std::string s;


  if (in.is_open()) {
    // 위치 지정자를 파일 끝으로 옮긴다.
    in.seekg(0, std::ios::end);


    // 그리고 그 위치를 읽는다. (파일의 크기)
    int size = in.tellg();


    // 그 크기의 문자열을 할당한다.
    s.resize(size);


    // 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
    in.seekg(0, std::ios::beg);


    // 파일 전체 내용을 읽어서 문자열에 저장한다.
    in.read(&s[0], size);
    std::cout << s << std::endl;
  } else {
    std::cout << "파일을 찾을 수 없습니다!" << std::endl;
  }


  return 0;
```


- 파일 끝으로 이동 : std::seekg(0, std::ios::end) 
- 이 함수의 첫번째 인자는 스트림에서부터 offset 크기 만큼 이동해 스트림을 가리는 것이며 두번째 인자는 이 스트림의 시작을 끝에서 시작한다는 것을 가리킨다.
- 대신 첫번째 인자에 std::ios::end값을 넣어주면 2라는 숫자로 들어가 두번째 스트림값을 가리키게 된다.
- tellg() 에 대한 설명 : 단순히 파일의 위치값을 기억하고 다시 사용할 수 있게 int 값으로 반환된다. 이를 이용해서 같은 위치의 스트림으로 가서 수정도 할수 있도록 도와주는 함수. 대신에 파일의 크기를 알려주거나 하지는 않는다. 오히려 포인터 값으로 반환되는 것은 tellp() 가 있다.



## 파일 전체를 한 줄 씩 읽기

```
// getline 으로 읽어들이기#include <fstream>#include <iostream>#include <string>


int main() {
  // 파일 읽기 준비
  std::ifstream in("test.txt");
  char buf[100];


  if (!in.is_open()) {
    std::cout << "파일을 찾을 수 없습니다!" << std::endl;
    return 0;
  }


  while (in) {
    in.getline(buf, 100);
    std::cout << buf << std::endl;
  }


  return 0;
}

```


- getline 은 ifstream 클래스의 멤버 함수로 존재한다. 작동 방식은 단순한대 '\n" 값이 나올때 마다 한줄씩 읽어오며  널값은 지워버립니다.
- getline 활용 : 
    in.getline(buf, 100, '.') : 100자중 99자 까지 읽을 수 있으며 마침표가 나올때까지 읽어온다. char 대신 string 을 사용하면 크기에 상관없이 끝까지 파일을 읽어올 수 있다.




# 파일 쓰기
```
#include <iostream>#include <fstream>#include <string>


int main() {
  // 파일 쓰기 준비
  std::ofstream out("test.txt");


  std::string s;
  if (out.is_open()) {
    out << "이걸 쓰자~~";
  }


  return 0;
}
```


- 특별한 내용 설정하지 않는다면 전부 지워지고 새로운 내용으로 덮어씌어지게 된다.



```
#include <fstream>#include <iostream>#include <string>


int main() {
  // 파일 쓰기준비
  std::ofstream out("test.txt", std::ios::app);


  std::string s;
  if (out.is_open()) {
    out << "덧붙이기";
  }


  return 0;
}
```
- std::ios::app 비트 마스킹을 해주면 새로운 내용이 덮어씌어지게 되는데 앞에서 나왔던 std::ios::binary 말고도 더있다.


- ios::binary : 이진수로 읽는다.
- ios::app : 이어붙이기
- ios::ate : 자동으로 파일 끝에서 부터 읽기와 쓰기 실시
- ios::trunc : 파일 스트림을 열면 기존에 있는 내용 삭제
- ios::in : 파일 입력 ifstream 에서 이미 설정
- ios::out : 파일 출력 ifstream : 에서 이미 설정




