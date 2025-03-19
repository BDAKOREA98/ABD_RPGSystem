// ABD


#include "Weapon/C_WeaponBase.h"
#include "Components/BoxComponent.h"
#include "Creature/C_Enemy.h"
#include "C_FunctionLibrary.h"
#include "MyDebugHelper.h"


AC_WeaponBase::AC_WeaponBase()
{

	PrimaryActorTick.bCanEverTick = false;


	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetBoxExtent(FVector(20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlab);
	CollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlab);


}

void AC_WeaponBase::OnCollisionBoxBeginOverlab(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to Assign an Instigator as the Owning pawn for the Weapon %s "), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UC_FunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}

	}

}

void AC_WeaponBase::OnCollisionBoxEndOverlab(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to Assign an Instigator as the Owning pawn for the Weapon %s "), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UC_FunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}

	}
}
