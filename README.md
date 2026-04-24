# Unreal-WarLegend

> UE 5.7 · C++ · GAS · MVVM

방치형 RPG + 보스 1v1 액션 전투 데모 입니다.

---

## Architecture

**순수 MVVM** 패턴 적용

```
View → ViewModel → Manager (단방향 의존)
```

### View

- 자신의 VM을 생성 · 소유 (Base코드를 상속받아서 BindViewModel라는 공통 함수를 만들고 VM 생성 후 주입)
- VM 델리게이트를 구독하여 UMG 렌더링만 담당

| 분류 | 설명 |
|------|------|
| `Hud` | 플레이어 상태, 몬스터 HP 등 게임 중 상시 노출되는 정보 표시 |
| `Popup` | 던전 선택, 뽑기, 필터 등 특정 행동 시 열리는 모달 UI |
| `Screen` | 인벤토리, 타이틀 등 전체 화면을 차지하는 UI |
| `Slot` | 아이템 슬롯, 던전 목록 항목 등 리스트 내 반복 사용되는 단위 위젯 |

### ViewModel

- 데이터 보유 + 델리게이트 변경 통지
- Manager를 직접 참조하여 비즈니스 명령 실행 및 이벤트 구독 (던전 입장, 필터 변경, 인벤토리 갱신 등)
- 자식 VM 생성 · 소유 (예: `ScreenInventoryVM`이 `SlotInventoryVM` 배열 관리)
- 하위 VM에서 올라온 요청을 상위로 릴레이 (아이템 상세 팝업 오픈 등)

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
| `InventoryManager` | 아이템 추가 · 삭제 · 조회, 동일 ID 아이템 획득 시 수량 스택 처리 |


## Tech Stack

`Unreal Engine 5.7` · `C++` · `Gameplay Ability System` · `Behavior Tree`
