// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XGameplayInterface.h"
#include "XItemChest.generated.h"

class UTimelineComponent;

UCLASS()
class DEMO_API AXItemChest : public AActor, public IXGameplayInterface
{
	GENERATED_BODY()

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	float TargetPitch;
	
public:	
	// Sets default values for this actor's properties
	AXItemChest();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UParticleSystemComponent* BonusComp;

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BonusMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
