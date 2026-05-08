# DataMonitor

C++ 콘솔 기반 데이터 모니터링 도구 (PoC)

---

## 소개

DataMonitor는 JSON 파일에 저장된 주문(Order) 및 시료(Sample) 데이터를 콘솔에서 조회하고 상태를 모니터링하는 관리자 도구입니다.

외부 서버, DB, SQLite 없이 로컬 JSON 파일만을 데이터 소스로 사용하며, 이전 PoC에서 검증한 MVC 구조와 JSON 영속성 레이어를 재사용합니다.

---

## 실행 방법

### 요구 환경

- Windows 10/11
- Visual Studio 2022 (MSVC, C++17 이상)

### 빌드 및 실행

1. `DataMonitor.vcxproj`를 Visual Studio로 열기
2. 빌드 구성: `Debug` 또는 `Release`, 플랫폼: `x64`
3. **빌드 → 솔루션 빌드** 실행
4. 생성된 실행 파일 실행 또는 Visual Studio에서 **F5** 실행

### 데이터 파일 위치

실행 파일 기준 상대 경로로 `data/` 디렉토리를 참조합니다.

- Visual Studio 디버그 실행 시: 프로젝트 루트의 `data/` 참조
- 파일이 없을 경우 빈 초기 파일이 자동 생성됩니다.

---

## 모니터링 기능

### 메인 메뉴

```
1. 시료 관리
2. 주문 관리
3. 생산 라인 관리
4. 모니터링
5. 출하 관리
0. 종료
```

### 모니터링 서브메뉴

```
1. 전체 Dashboard
2. 주문 상태별 집계
3. 시료 재고 현황
0. 돌아가기
```

### 기능 상세

| 기능 | 설명 |
|---|---|
| 전체 Dashboard | 주문 상태 집계 + 시료 목록을 한 화면에 표시 |
| 주문 상태별 집계 | 접수 / 처리 중 / 완료 / 취소 건수 및 합계 표시 |
| 시료 재고 현황 | ID, 이름, 설명 목록 표시 |

---

## JSON 데이터 파일

### data/samples.json

시료 데이터를 저장합니다.

| 필드 | 타입 | 설명 |
|---|---|---|
| nextId | int | 다음 생성 시 부여할 ID |
| items | array | 시료 객체 목록 |
| items[].id | int | 시료 고유 ID |
| items[].name | string | 시료 이름 |
| items[].description | string | 시료 설명 |

### data/orders.json

주문 데이터를 저장합니다.

| 필드 | 타입 | 설명 |
|---|---|---|
| nextId | int | 다음 생성 시 부여할 ID |
| items | array | 주문 객체 목록 |
| items[].id | int | 주문 고유 ID |
| items[].productName | string | 제품명 |
| items[].quantity | int | 수량 |
| items[].status | string | 상태 (`접수` / `처리 중` / `완료` / `취소`) |

### 파일 구조 예시

```json
{
  "nextId": 4,
  "items": [
    {"id": 1, "productName": "제품A", "quantity": 10, "status": "접수"},
    {"id": 2, "productName": "제품B", "quantity": 5,  "status": "완료"},
    {"id": 3, "productName": "제품C", "quantity": 3,  "status": "처리 중"}
  ]
}
```

---

## 콘솔 화면

### 전체 Dashboard

```
============================================
         DataMonitor — Dashboard
============================================

 [주문 현황]
  접수      :   5 건
  처리 중   :   3 건
  완료      :  12 건
  취소      :   1 건
  ─────────────────────
  합계      :  21 건

 [시료 재고 현황]
  ID   이름           설명
  ─────────────────────────────────────────
   1   sample1        test sample1
   2   sample2        test sample2

============================================
계속하려면 Enter를 누르세요...
```

### 주문 상태별 집계

```
============================================
         주문 상태별 집계
============================================
  접수      :   5 건
  처리 중   :   3 건
  완료      :  12 건
  취소      :   1 건
  ─────────────────────
  합계      :  21 건
============================================
계속하려면 Enter를 누르세요...
```

### 시료 재고 현황

```
============================================
         시료 재고 현황
============================================
  ID   이름           설명
  ─────────────────────────────────────────
   1   sample1        test sample1
   2   sample2        test sample2
============================================
총 2건
계속하려면 Enter를 누르세요...
```

---

## 프로젝트 구조

```
DataMonitor/
├── data/
│   ├── samples.json
│   └── orders.json
├── src/
│   ├── models/
│   ├── repositories/
│   ├── persistence/
│   ├── services/
│   ├── controllers/
│   ├── views/
│   ├── utils/
│   └── main.cpp
├── tests/
│   └── README.md
├── .gitignore
├── CLAUDE.md
├── PRD.md
└── README.md
```
