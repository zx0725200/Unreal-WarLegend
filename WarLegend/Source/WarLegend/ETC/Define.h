#pragma once

#define GTGetMgrImpl(SubSystemClassName) (GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<SubSystemClassName>()->MgrImpl : nullptr)
#define GTGetMgr(SubSystemClassName) (GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<SubSystemClassName>() : nullptr)
#define GTUIGetMgr(SubSystemClassName) (GetOwningLocalPlayer() ? GetOwningLocalPlayer()->GetSubsystem<SubSystemClassName>() : nullptr)
#define GTUIGetMgrImpl(SubSystemClassName) (GetOwningLocalPlayer() ? GetOwningLocalPlayer()->GetSubsystem<SubSystemClassName>()->MgrImpl : nullptr)

