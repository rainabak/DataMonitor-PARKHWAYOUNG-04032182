# CLAUDE.md — DataMonitor 작업 규칙

이 파일은 Claude가 DataMonitor 프로젝트에서 작업할 때 반드시 준수해야 하는 규칙을 정의합니다.

---

## Claude 작업 규칙

### 기본 원칙

- 요청받은 범위만 구현한다. 요청 외 기능을 자의적으로 추가하지 않는다.
- 코드 작성 전에 반드시 관련 파일을 읽고 기존 구조를 파악한다.
- 기존 코드 스타일, 네이밍, 패턴을 유지한다. 리팩터링은 별도 지시가 있을 때만 수행한다.
- 한 번에 하나의 책임만 변경한다. 여러 계층을 동시에 수정하지 않는다.
- 불필요한 주석, 임시 코드(`// TODO`, `// FIXME`), 미사용 변수를 남기지 않는다.

### 응답 규칙

- 지시에 "코드 작성 금지"가 명시된 경우 설계·문서 작업만 수행한다.
- 파일 전체 코드를 응답에 출력하지 않는다. 변경된 부분만 표시한다.
- 코드 변경 후 변경 사유를 한 줄로 설명한다.

### 금지 사항

- DB, SQLite, 외부 서버 관련 코드 작성 금지
- 기존 영속성 레이어(`JsonFileStorage`, `JsonUtil`)를 우회하는 파일 직접 접근 금지
- 전역 변수 사용 금지
- `using namespace std;` 사용 금지

---

## C++ 코딩 규칙

### 네이밍

| 대상 | 규칙 | 예시 |
|---|---|---|
| 클래스, 구조체 | PascalCase | `MonitoringService` |
| 메서드, 함수 | camelCase | `findAll`, `getMenuChoice` |
| 멤버 변수 | `m_` 접두사 + camelCase | `m_orders`, `m_nextId` |
| 매개변수, 지역 변수 | camelCase | `orderList`, `choice` |
| 상수 | UPPER_SNAKE_CASE | `MAX_ITEMS` |
| 헤더 가드 | UPPER_SNAKE_CASE + `_H` | `MONITORING_SERVICE_H` |

### 파일 구조

- 헤더 파일(`.h`)에는 선언만, 소스 파일(`.cpp`)에는 구현만 위치한다.
- 헤더 파일에는 반드시 헤더 가드(`#ifndef ... #define ... #endif`)를 사용한다.
- `#pragma once`와 헤더 가드를 혼용하지 않는다. 헤더 가드를 기본으로 사용한다.

### 타입 사용

- 문자열은 `std::string`을 사용한다.
- 컬렉션은 `std::vector`를 기본으로 사용한다.
- 포인터 반환이 필요한 경우(nullable) `T*`를 사용한다. 소유권 이전 없이 단순 참조 목적으로만 사용한다.
- 스마트 포인터는 이번 PoC 범위에서 사용하지 않는다.

### 기타

- 함수는 하나의 책임만 갖는다.
- 함수 길이는 30줄을 초과하지 않도록 작성한다.
- 중첩 깊이는 3단계를 초과하지 않는다.
- `std::` 접두사를 명시적으로 사용한다.

---

## MVC 역할 분리 규칙

### Model (models/)

- 데이터 구조(`struct`)만 정의한다.
- 비즈니스 로직, 집계 로직, UI 로직을 포함하지 않는다.
- 외부 의존성(Repository, Service 등)을 갖지 않는다.

### Repository (repositories/)

- 데이터의 CRUD 연산만 담당한다.
- 집계 로직을 포함하지 않는다.
- `JsonFileStorage`를 통해서만 파일에 접근한다.
- 인터페이스(`IOrderRepository`, `ISampleRepository`)를 구현한다.

### Service (services/)

- Repository에서 데이터를 읽어 집계·가공하는 로직을 담당한다.
- View와 직접 통신하지 않는다.
- 파일에 직접 접근하지 않는다. Repository 인터페이스를 통해서만 데이터를 접근한다.

### Controller (controllers/)

- Service와 View 사이의 흐름을 조율한다.
- 집계 로직, 표시 로직을 직접 포함하지 않는다.
- Service로부터 결과를 받아 View에 전달하는 역할만 한다.

### View (views/)

- 표시(출력)와 입력 수집만 담당한다.
- 비즈니스 로직, 집계 로직, 파일 접근을 포함하지 않는다.
- Controller가 전달한 데이터를 그대로 화면에 출력한다.

### 의존성 방향

```
main.cpp (DI)
  → Controller → Service → Repository → JsonFileStorage
  → Controller → View
```

역방향 의존성은 허용하지 않는다. (예: Repository가 Controller를 참조하는 것 금지)

---

## JSON 파일 직접 접근 제한 규칙

- `fstream`, `ifstream`, `ofstream`을 사용한 파일 직접 접근은 `JsonFileStorage`와 `JsonUtil`에서만 허용한다.
- `persistence/` 계층 외부에서 파일 경로 문자열을 직접 조합하거나 파일을 열지 않는다.
- `data/` 디렉토리 경로는 `main.cpp`의 DI 구성 시점에만 정의한다.
- JSON 파싱은 `JsonUtil`의 함수만 사용한다. 직접 문자열 파싱을 새로 작성하지 않는다.

---

## Clean Code 규칙

### 주석

- 코드 자체로 의도가 명확한 경우 주석을 작성하지 않는다.
- "무엇을 하는가(What)"가 아닌 "왜 이렇게 했는가(Why)"가 비자명한 경우에만 주석을 작성한다.
- 다중 줄 주석 블록(`/* ... */`)은 사용하지 않는다.

### 중복 제거

- 동일한 출력 형식(구분선, 헤더 등)은 `ConsoleUtil`에 공통 함수로 추출한다.
- 동일한 JSON 파싱 패턴은 `JsonUtil`에 함수로 추출한다.

### 매직 넘버 / 매직 스트링 제거

- 상태 문자열(`"접수"`, `"처리 중"` 등)은 상수로 정의하거나 한 곳에서 관리한다.
- 화면 너비(구분선 길이 등)는 상수로 정의한다.

### 오류 처리

- 예외는 사용자에게 의미있는 메시지로 변환하여 출력한다.
- 프로그램을 강제 종료(`exit()`, `abort()`)하지 않는다. 메뉴로 복귀한다.

---

## Commit 규칙

### Commit 메시지 형식

```
<type>: <subject>
```

- 제목은 50자 이하로 작성한다.
- 현재 시제, 명령형으로 작성한다. (예: `add`, `implement`, `fix`, `update`)

### Type 목록

| Type | 사용 시점 |
|---|---|
| `feat` | 새로운 기능 추가 |
| `fix` | 버그 수정 |
| `refactor` | 기능 변경 없는 코드 구조 개선 |
| `docs` | 문서 작성 및 수정 |
| `chore` | 빌드 설정, 프로젝트 파일 변경 |
| `test` | 테스트 시나리오 추가 및 수정 |
| `data` | JSON Seed 데이터 추가 및 수정 |

### Commit 단위 원칙

- 하나의 commit은 하나의 논리적 변경만 포함한다.
- 여러 계층을 동시에 수정하는 commit을 만들지 않는다.
  - 잘못된 예: `feat: add MonitoringService and MonitoringView and MonitoringController`
  - 올바른 예: 계층별로 별도 commit
- 빌드가 깨지는 상태에서 commit하지 않는다.
- `.vcxproj` 변경은 관련 소스 파일 추가 직후 별도 commit으로 분리한다.

### 금지 사항

- `--no-verify` 옵션 사용 금지
- `git push --force` 사용 금지 (main 브랜치 기준)
- 민감 정보(패스워드, API 키)가 포함된 파일 commit 금지
