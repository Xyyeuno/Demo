// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/XAttributeTypes.h"
#include "XAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, AActor*, InstigatoActor, UXAttributeComponent*, OwningComp, float, maxHealth, float, newHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DEMO_API UXAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeProperty")
	TMap<EAttributePropertyName, FAttributePropertyValue> AttributeProperties;
	
public:	

	// Sets default values for this component's properties
	UXAttributeComponent();

	UFUNCTION(BlueprintPure)
	FORCEINLINE FAttributePropertyValue& GetAttributePropertyStructWithName(EAttributePropertyName Name);

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAttributePropertyValueWithName(EAttributePropertyName Name);

	//血量变化组件
	UFUNCTION(BlueprintCallable)
	bool ModifyAttributePropertyValue(EAttributePropertyName Name, float Delta, bool bUpdateUI);

	UFUNCTION(BlueprintCallable)
	bool SetAttributePropertyValue(EAttributePropertyName Name, float NewValue, bool bUpdateUI);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateAttributePropertyUI(EAttributePropertyName Name);
	UFUNCTION()
	virtual void UpdateAttributePropertyUI(EAttributePropertyName Name);

	UFUNCTION(BlueprintCallable)
	bool isAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION()
	bool SetDefaultHealth(float _MaxHealth);

	UFUNCTION()
	bool ApplyHealthChange(float Delta);

};
