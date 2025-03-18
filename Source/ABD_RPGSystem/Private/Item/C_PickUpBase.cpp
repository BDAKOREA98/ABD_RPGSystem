// ABD


#include "Item/C_PickUpBase.h"

// Sets default values
AC_PickUpBase::AC_PickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_PickUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

