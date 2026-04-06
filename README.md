# Unreal-WarLegend

> UE 5.7 · C++ · GAS · MVVM

방치형 RPG + 보스 1v1 액션 전투 데모  
워크래프트3 유즈맵에서 영감을 받은 프로젝트입니다.

---

## Architecture

**MVVM + Presenter** 패턴 적용  

```
View → ViewModel → Manager (단방향 의존)
         ↑
     Presenter (VM 생성 · View-VM 바인딩)
```

### Presenter

| 클래스 | 역할 |
|--------|------|
| `UIFlowPresenter` | 최상위 진입점 (`LocalPlayerSubsystem`). 도메인별 Presenter 소유 |
| `DungeonPresenter` | 던전 UI 흐름, 몬스터 HeadUp VM 생성 |
| `GachaPresenter` | 뽑기 · 필터 · 로그 UI 흐름 |
| `InventoryPresenter` | 인벤토리 UI 흐름, 아이템 상세 팝업 연결 |

- VM 생성 → View에 주입
- 크로스 UI 이벤트 처리 (토스트 표시, 아이템 상세 팝업 등)

### ViewModel

- 데이터 보유 + 델리게이트 변경 통지
- Manager를 직접 참조하여 비즈니스 명령 실행 (던전 입장, 필터 변경 등)

### View

- VM을 주입받아 UMG 갱신만 담당, 자체 로직 없음

| 분류 | 설명 |
|------|------|
| `Hud` | 상시 표시 UI |
| `Popup` | 모달 UI |
| `Screen` | 전체화면 UI |
| `Slot` | 재사용 단위 |

### Manager (SubSystem)

컨텐츠별 데이터 · 비즈니스 로직 담당

**GameInstanceSubsystem** — 전역 데이터

| Manager | 역할 |
|---------|------|
| `UIManager` | DataAsset 기반 UI 등록, FName 키로 Show/Hide 관리 |
| `TableManager` | DataTable 로드 후 캐싱, 조회 인터페이스 제공 |
| `SaveGameDataManager` | 언리얼 SaveGame으로 인벤토리 · 뽑기 필터 영속화 |
| `GachaManager` | 등급별 가중치 확률 뽑기, 필터 적용 |
| `DungeonManager` | 던전 데이터 관리, 몬스터 스폰 및 생존 카운트 추적 |

**LocalPlayerSubsystem** — 플레이어 귀속 데이터

| Manager | 역할 |
|---------|------|
| `InventoryManager` | 아이템 CRUD, 동일 ID 아이템 획득 시 수량 스택 처리 |

---

## Tech Stack

`Unreal Engine 5.7` · `C++` · `Gameplay Ability System` · `Behavior Tree` ·
