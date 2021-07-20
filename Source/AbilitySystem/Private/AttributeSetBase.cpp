// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

UAttributeSetBase::UAttributeSetBase()
	: m_Health(200.0f)
	, m_MaxHealth(200.0f)
	, m_Mana(100.0f)
	, m_MaxMana(100.0f)
{

}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, m_Health)))
	{
		m_Health.SetCurrentValue(FMath::Clamp(m_Health.GetCurrentValue(), 0.0f, m_MaxHealth.GetCurrentValue()));
		m_Health.SetBaseValue(FMath::Clamp(m_Health.GetBaseValue(), 0.0f, m_MaxHealth.GetCurrentValue()));

		OnHealthChange.Broadcast(m_Health.GetCurrentValue(), m_MaxHealth.GetCurrentValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, m_Mana)))
	{
		m_Mana.SetCurrentValue(FMath::Clamp(m_Health.GetCurrentValue(), 0.0f, m_MaxMana.GetCurrentValue()));
		m_Mana.SetBaseValue(FMath::Clamp(m_Health.GetBaseValue(), 0.0f, m_MaxMana.GetCurrentValue()));

		OnHealthChange.Broadcast(m_Mana.GetCurrentValue(), m_MaxMana.GetCurrentValue());
	}
}
