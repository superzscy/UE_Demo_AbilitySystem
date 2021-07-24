// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AttributeSetBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	m_AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBaseComp");
	m_bIsDead = false;
	m_TeamID = 255;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	m_AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &ACharacterBase::OnHealthChange);
	m_AttributeSetBaseComp->OnManaChange.AddDynamic(this, &ACharacterBase::OnManaChange);
	AutoDeterminTeamID();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return m_AbilitySystemComp;
}

void ACharacterBase::AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire)
{
	if (m_AbilitySystemComp)
	{
		if (HasAuthority() && AbilityToAcquire)
		{
			m_AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAcquire, 1, 0));
		}
		m_AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

bool ACharacterBase::IsHostileTo(ACharacterBase* Other)
{
	return m_TeamID != Other->m_TeamID;
}

void ACharacterBase::OnHealthChange(float CurValue, float MaxValue)
{
	if (CurValue <= 0 && !m_bIsDead)
	{
		m_bIsDead = true;
		BP_Die();
	}

	BP_OnHealthChanged(CurValue, MaxValue);
}

void ACharacterBase::OnManaChange(float CurValue, float MaxValue)
{
	BP_OnManaChanged(CurValue, MaxValue);
}

void ACharacterBase::AutoDeterminTeamID()
{
	AController* pController = GetController();
	if (pController && pController->IsPlayerController())
	{
		m_TeamID = 0;
	}
}

