// ABD


#include "Weapon/C_ProjectileBase.h"

// Sets default values
AC_ProjectileBase::AC_ProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_ProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_ProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

