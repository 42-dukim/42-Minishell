# **minishell**

유닉스 셸의 핵심 기능을 C언어로 구현한 42 경산 과제입니다. 이 프로젝트를 통해 프로세스 제어, IPC(Inter-Process Communication), 시스템 콜에 대한 깊은 이해를 얻을 수 있었습니다.

---

### **👨‍💻 팀 소개 (Contributors)**

| Profile                                             | Name                                             | Role & Responsibility                                                                                                 |
| :-------------------------------------------------- | :----------------------------------------------- | :-------------------------------------------------------------------------------------------------------------------- |
| <img src="https://github.com/iamdudumon.png" width="80"> | [@iamdudumon](https://github.com/iamdudumon)     | **명령어 해석 파트 (Parser)**<br/>- Tokenizer & Parser 설계 및 구현<br/>- 따옴표, 리다이렉션 등 복잡한 셸 문법 처리 |
| <img src="https://github.com/composerboyV.png" width="80"> | [@composerboyV](https://github.com/composerboyV) | **내장 명령어 파트 (Built-in)**<br/>- `cd`, `export`, `unset` 등 내장 명령어 구현<br/>- 명령어 실행 및 프로세스 관리 |

## **✨ 주요 기능 (Features)**

- **명령어 실행**: `PATH` 환경변수를 기반으로 한 외부 명령어 실행
- **파이프라이닝 (`|`)**: 여러 개의 명령어를 파이프로 연결하여 동시에 실행
- **리다이렉션 (`<`, `>`, `>>`)**: 명령어의 입출력을 파일로 재지정
- **Here Document (`<<`)**: 지정된 Delimiter까지의 입력을 받아 임시 파일로 처리
- **내장 명령어 (Built-ins)**: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset` 구현
- **환경 변수 치환**: `$KEY` 및 `$?` (종료 코드) 형태의 환경 변수 확장
- **시그널 처리**: `Ctrl+C`, `Ctrl+D`, `Ctrl+\` 시그널에 대한 안정적인 처리

---

## **🏛️ 아키텍처 (Architecture)**

본 프로젝트는 명령어 처리 과정을 명확하게 분리하기 위해 **`Tokenizer` -\> `Parser` -\> `Executor`** 파이프라인 구조로 설계되었습니다.

1.  **Tokenizer**: 사용자 입력을 `WORD`와 `SYMBOL` 단위의 토큰 리스트로 분해합니다.
2.  **Parser**: 토큰 리스트를 분석하여 파이프를 기준으로 나뉜 실행 가능한 명령어(Command) 단위로 재구성합니다.
3.  **Executor**: 구성된 명령어를 시스템 콜(`fork`, `execve`, `pipe`, `dup2`)을 통해 실행하고 프로세스를 관리합니다.

예시 흐름
```
입력:   echo "a b" | grep $X >> out.txt
토큰:   ["echo"(W), "a b"(W), "|"(S), "grep"(W), "$X"(W), ">>"(S), "out.txt"(W)]
유닛:   cmd0: args=["echo","a b"], redi=[]
        cmd1: args=["grep", EXPAND(X)], redi=[type='+'(">>"), file="out.txt"]
실행:   [cmd0] → pipe → [cmd1 with append redirection]
```

---

## **🛠️ 시작하기 (Getting Started)**

### **Requirements**

- OS/툴체인: Linux, gcc/clang, make.
- 라이브러리: readline (Ubuntu: sudo apt-get install libreadline-dev).
- 서브모듈/의존: libft (동일 리포 내 포함).

### **빌드**

```bash
# 기본 빌드
make

# 디버깅 빌드 (메모리 및 동작 오류 검사)
make dev
```

### **실행**

```bash
./minishell
```

#### 예시:

```bash
$ ls -al
$ echo hi | tr a-z A-Z > out.txt
cat out.txt
```    
<img width="411" height="362" alt="image" src="https://github.com/user-attachments/assets/66eece63-761f-4769-8aef-d2d825fddd10" />

```bash
$ ls libft | grep 'ft_str' > output.txt
$ cat output.txt
```
<img width="411" alt="image" src="https://github.com/user-attachments/assets/bb7e4c31-070a-442f-8d9c-897072548a03" />

```bash
$ cat Makefile | grep c | sort | head -n 5
```

<img width="411" alt="image" src="https://github.com/user-attachments/assets/654dbcac-000c-49d6-a576-763a1ebb88a9" />

> #### 최근 Update logs
- Child exit: 자식 프로세스는 `execute_command` 결과로 즉시 `exit(code)` 처리
- Pipe/FD: 마지막 파이프 생략, `dup2` 직후 원 FD 즉시 `close`, 부모는 직전 read end 바로 닫음
- Builtin redirection: 빌트인은 `builtin_handler`, 외부 명령은 `execute_command`에서만 리다이렉션 적용/원복
- Dev mode: `make dev`로 ASan/UBSan flag를 포함한 빌드/실행
