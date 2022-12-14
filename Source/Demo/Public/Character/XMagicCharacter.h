// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/XCharacter.h"
#include "XMagicCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AXMagicCharacter : public AXCharacter
{
	GENERATED_BODY()

	float AttackAnimDelay;

	FTransform SpawnTM(FName SocketLocation);

protected:
	//ħ??
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	//????ħ??
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DashProjectileClass;

	//ħ??????
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	
	FTimerHandle TimerHandle_Dash;

public:
	AXMagicCharacter();

protected:

	//?????ṥ??
	virtual void MBLAttack() override;
	void MBLAttack_TimeElapsed();

	//?Ҽ??ع???
	virtual void MBRAttack() override;
	void MBRAttack_TimeElapsed();

	//???⼼?ܣ?ħ??????
	virtual void ExtraSkill() override;

	//????
	void Dash();
	void Dash_TimeElapsed();
	void SpawnProjectile(TSubclassOf<AActor> DashProjectile);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
