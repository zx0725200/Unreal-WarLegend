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

- `UIFlowPresenter`(`LocalPlayerSubsystem`)가 최상위 진입점
- VM 생성 → View에 주입
- UI의 표시 · 숨김 흐름 관리

### ViewModel

- 데이터 보유 + 델리게이트 변경 통지
- Manager를 직접 참조하여 비즈니스 명령 실행 (던전 입장, 필터 변경 등)

### View

- VM을 주입받아 UMG 갱신만 담당, 자체 로직 없음

| 분류 | 설명 |
|------|------|
| `Hud` | 플레이어 상태, 몬스터 HP 등 게임 중 상시 노출되는 정보 표시 |
| `Popup` | 던전 선택, 뽑기, 필터 등 특정 행동 시 열리는 중간 크기의 UI |
| `Screen` | 인벤토리, 타이틀 등 전체 화면을 차지하는 UI |
| `Slot` | 아이템 슬롯, 던전 목록 항목 등 리스트 내 반복 사용되는 단위 위젯 |

### Manager (SubSystem)

컨텐츠별 데이터 · 비즈니스 로직 담당

**GameInstanceSubsystem** — 전역 데이터

| Manager | 역할 |
|---------|------|
| `UIManager` | DataAsset 기반 UI 등록, FName 키로 Show/Hide 관리 |
| `TableManager` | DataTable 로드 후 캐싱, 조회 인터페이스 제공 |
| `SaveGameDataManager` | 언리얼 SaveGame으로 인벤토리 · 뽑기 필터 저장 및 로드 |
| `GachaManager` | 등급별 가중치 확률 뽑기, 필터 적용 |
| `DungeonManager` | 던전 데이터 관리, 몬스터 스폰 |

**LocalPlayerSubsystem** — 플레이어 귀속 데이터

| Manager | 역할 |
|---------|------|
| `InventoryManager` | 아이템 추가 · 삭제 · 조회, 동일 ID 아이템 획득 시 수량 스택 처리 |

---

## Tech Stack

`Unreal Engine 5.7` · `C++` · `Gameplay Ability System` · `Behavior Tree`
