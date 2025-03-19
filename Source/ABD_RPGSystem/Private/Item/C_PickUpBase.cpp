// ABD


#include "Item/C_PickUpBase.h"
#include "Components/SphereComponent.h"
// Sets default values
AC_PickUpBase::AC_PickUpBase()
{
 	
	
	PrimaryActorTick.bCanEverTick = false;

	PickUpCollisionSphere = CreateDefaultSubobject< USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(PickUpCollisionSphere);
	PickUpCollisionSphere->InitSphereRadius(50.f);
	PickUpCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnPickUpCollisionSphereBeginOverlap);

}

void AC_PickUpBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
