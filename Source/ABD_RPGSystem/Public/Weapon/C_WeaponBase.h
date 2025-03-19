// ABD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_WeaponBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTagetInteractedDelegate, AActor*)


UCLASS()
class ABD_RPGSYSTEM_API AC_WeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_WeaponBase();

	FOnTagetInteractedDelegate OnWeaponHitTarget;
	FOnTagetInteractedDelegate OnWeaponPulledFromTarget;


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* CollisionBox;

	UFUNCTION()

	virtual void OnCollisionBoxBeginOverlab(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlab(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);




public:

	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return CollisionBox; }


};
