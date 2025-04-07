#include "GGE2D/GGE2D_AnimInstance.h"

#include "GameplayTagContainer.h"
#include "OmegaGameplayTags.h"

#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "Characters/PlayerCharacters/PlayerBaseCharacter.h"


void UGGE2D_AnimInstance::OnInit_Implementation()
{
	GetEssentials();
}

bool UGGE2D_AnimInstance::GetEssentials()
{
	// Подтягиваем персонажа-владельца
	SourceCharacter = Cast<AOmegaCharacter>(GetOwningActor());
	if (!SourceCharacter) return false;

	// Подтягиваем из персонажа GAS
	SourceASC = Cast<UOmegaAbilitySystemComponent>(SourceCharacter->GetAbilitySystemComponent());
	if (!SourceASC) return false;

	// Dash
	SourceASC->RegisterGameplayTagEvent(FOmegaGameplayTags::Get().Animation_Dash, EGameplayTagEventType::NewOrRemoved).AddLambda([this](const FGameplayTag& InGameplayTag, int32 StackCount)
	{
		UpdateAnimationTags(InGameplayTag, StackCount);
	});

	// Death
	SourceASC->RegisterGameplayTagEvent(FOmegaGameplayTags::Get().Animation_Death, EGameplayTagEventType::NewOrRemoved).AddLambda([this](const FGameplayTag& InGameplayTag, int32 StackCount)
	{
		UpdateAnimationTags(InGameplayTag, StackCount);
	});

	// Attack
	SourceASC->RegisterGameplayTagEvent(FOmegaGameplayTags::Get().Animation_Attack, EGameplayTagEventType::NewOrRemoved).AddLambda([this](const FGameplayTag& InGameplayTag, int32 StackCount)
	{
		UpdateAnimationTags(InGameplayTag, StackCount);
	});
	
	return true;
}

/*
 * Собственно смотрим добавить нам тег в контейнер или удалить его.
 */
void UGGE2D_AnimInstance::UpdateAnimationTags(const FGameplayTag& InGameplayTag, int32 StackCount)
{
	if (StackCount > 0) AnimationTags.AddTag(InGameplayTag);
	else AnimationTags.RemoveTag(InGameplayTag);
}
void UGGE2D_AnimInstance::OnTick_Implementation(float DeltaTime)
{
	/*
	 * Функция OnInit (аналог BeginPlay), по моему опыту, срабатывает не стабильно - может успеть задать персонажа и др. параметры, а может нет.
	 * Поэтому я дублирую функцию в OnTick, чтобы быть уверенным, что все важные параметры 100% подтянулись.
	 * В данном случае это не критично потому что никакой логики в OnTick нет, но если в будущем здесь будет запускаться логика зависящая к примеру от SourceASC,
	 * то могу полететь криты так как OnTick будет срабатывать быстрее чем OnInit присвоить этому полю значение.
	 */
	if (!GetEssentials())
	{
		GetEssentials();
	}
}


