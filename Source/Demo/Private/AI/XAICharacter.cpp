// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Component/XAttributeComponent.h"
#include "BrainComponent.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget/XWorldUserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AXAICharacter::AXAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	//创建血量组件
	AttributeComp = CreateDefaultSubobject<UXAttributeComponent>("AttributeComp");
	AttributeComp->SetDefaultHealth(50);
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);
	//GetMesh()->SetGenerateOverlapEvents(true);


	TimeHitParamName = "TimeToHit";
}

void AXAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AXAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &AXAICharacter::OnHealthChanged);
}

void AXAICharacter::OnHealthChanged(AActor* InstigatorActor, UXAttributeComponent* OwningComp, float maxHealth, float newHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}
	
		if (ActiveHealthBar == nullptr)
		{
			if (ensure(HealthBarWidgetClass))
			{
				ActiveHealthBar = CreateWidget<UXWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
				if (ActiveHealthBar)
				{
					ActiveHealthBar->AttachedActor = this;
					ActiveHealthBar->AddToViewport();
				}
			}
		}

		GetMesh()->SetScalarParameterValueOnMaterials(TimeHitParamName, GetWorld()->TimeSeconds);

		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);

		//Died
		if (newHealth <= 0.0f)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			//Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			SetLifeSpan(10.0f);
		}
	}
}

void AXAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}


void AXAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);

	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}

