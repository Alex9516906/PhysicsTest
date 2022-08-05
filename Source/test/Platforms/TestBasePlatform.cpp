
#include "TestBasePlatform.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "test/testCharacter.h"
#include "test/Base/TestGameMode.h"

ATestBasePlatform::ATestBasePlatform()
{
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
	PlatformMesh->SetupAttachment(RootComponent);
	
	GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ATestBasePlatform::OnBarrierComponentHit);
}

void ATestBasePlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Since this logic does not affect the gameplay, it can be implemented in a tick without replication*/
	if(bIsActive && HasAuthority())
		PlatformMesh->AddRelativeRotation(SpeedDownPlatform);
}

void ATestBasePlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATestBasePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	if(ATestGameMode* GameMode = Cast<ATestGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->OnStartPlatformDelegate.AddUObject(this, &ATestBasePlatform::StartPlay);
	}
}

void ATestBasePlatform::SetVelocity()
{
	GetStaticMeshComponent()->SetPhysicsAngularVelocityInRadians(NewAngVelocityBarrier);
}

void ATestBasePlatform::OnBarrierComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AtestCharacter* Character = Cast<AtestCharacter>(OtherActor))
	{
		
		FVector Impuls = NormalImpulse.GetSafeNormal();
		Character->GetCharacterMovement()->AddImpulse(Impuls*StrengthIpulse,true);
		GetStaticMeshComponent()->SetPhysicsAngularVelocityInRadians(NewAngVelocityBarrier);
	}
}

void ATestBasePlatform::StartPlay()
{
	GetWorld()->GetTimerManager().SetTimer(TimerSetVelocityRotation, this, &ATestBasePlatform::SetVelocity,RateSpeedTimerVelocity,true);
	bIsActive = true;
}

