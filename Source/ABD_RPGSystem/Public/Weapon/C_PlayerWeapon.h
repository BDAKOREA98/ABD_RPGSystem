// ABD

#pragma once

#include "CoreMinimal.h"
#include "Weapon/C_WeaponBase.h"
#include "Types/StructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "C_PlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API AC_PlayerWeapon : public AC_WeaponBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FPlayerWeaponData PlayerWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;




private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

};
