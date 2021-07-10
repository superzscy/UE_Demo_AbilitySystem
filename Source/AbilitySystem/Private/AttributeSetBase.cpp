// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

UAttributeSetBase::UAttributeSetBase()
	: m_Health(200.0f)
	, m_MaxHealth(200.0f)
{

}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, m_Health)))
	{
		m_Health.SetCurrentValue(FMath::Clamp(m_Health.GetCurrentValue(), 0.0f, m_MaxHealth.GetCurrentValue()));
		m_Health.SetBaseValue(FMath::Clamp(m_Health.GetBaseValue(), 0.0f, m_MaxHealth.GetCurrentValue()));

		UE_LOG(LogTemp, Warning, TEXT("Ouch, i took damage, now my health is : %f"), m_Health.GetCurrentValue());

		OnHealthChange.Broadcast(m_Health.GetCurrentValue(), m_MaxHealth.GetCurrentValue());
	}
}
