// ABD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ProjectileBase.generated.h"

UCLASS()
class ABD_RPGSYSTEM_API AC_ProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
