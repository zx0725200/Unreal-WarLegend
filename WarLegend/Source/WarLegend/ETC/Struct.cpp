
#include "Struct.h"

#include "Ability/WarriorAbility.h"
#include "DataTable/ItemTableData.h"

void FMyItem::Init(const FItemTableData* InTableData, const FLinearColor& InGradeColor, const int32 InUniqueID)
{
	UniqueID	   = InUniqueID;
	ID             = InTableData->ID;
	ItemName       = InTableData->ItemName;
	ItemTypeName   = InTableData->ItemTypeName;
	ItemType       = InTableData->ItemType;
	ItemGrade      = InTableData->ItemGrade;
	ItemGradeColor = InGradeColor;
	HP             = InTableData->HP;
	ATK            = InTableData->ATK;
	DEF            = InTableData->DEF;
}

bool FWarriorHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
