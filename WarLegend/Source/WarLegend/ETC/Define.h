#pragma once

#define GTGetMgrImpl(SubSystemClassName) (GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<SubSystemClassName>()->MgrImpl : nullptr)

