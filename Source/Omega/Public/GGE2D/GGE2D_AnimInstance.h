#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PaperZDAnimInstance.h"
#include "GGE2D_AnimInstance.generated.h"

class UOmegaAbilitySystemComponent;
class AOmegaCharacter;
class UAbilitySystemComponent;

/*
 * ОСНОВНАЯ КОНЦЕПЦИЯ:
 *
 * 1. Предполагается что теги передвижения будут накладываться через GameplayEffect
 * 2. Gas персонажа отслеживает поступление тега и срабатывает делегат RegisterGameplayTagEvent, к которому мы заранее привязываем логику Анимации в этом AnimInstance.
 *
 *
 * КАК ВЫГЛЯДИТ ЛОГИКА В ЭТОМ КЛАССЕ:
 * 
 * 1. В момент инициализации AnimInstance(функция OnInit) пытаемся получить персонажа-владельца и его GAS. Лучше если класс персонажа будет базовым, родительским классом и для игрока и для AI-персонажа - в таком случае
 *	  можно будет использовать одни AnimInstance для обоих.
 * 2. Из GAS персонажа получаем делегат RegisterGameplayTagEvent, который будет срабатывать каждый раз когда на GAS будет накладываться тег передвижения.
 * 3. Добавляем этот тег в тег-контейнер, который видит Animation Blueprint Instance и в зависимости от тега в контейнере StateMachine совершает переход в ту или иную анимацию.
 *
 *
 * НЮАНСЫ:
 *
 * 1. У меня все теги лежат в структуре-синглтоне FOmegaGameplayTags. От туда их получает AssetManger.
 * 2. Теги я свободно получаю из любого класса обращаясь к синглтону. Рекомендую такой подход, но если не нравится, надо придумать как передать теги передвижения делегату.
 * 3. Также у персонажа-владельца должен быть компонента UPaperZDAnimationComponent. UPaperSpriteComponent НЕ ПОДОЙДЕТ - в нем отсутствует AnimInstance, есть только UPaperSprite.
 */
UCLASS()
class OMEGA_API UGGE2D_AnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()

protected:

	/*
	 * Это тег-контейнер в который будут попадать теги передвижения при применении. StateMachine в блюпринте будет реагировать на наличие тегов в нем.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GGE2D")
	FGameplayTagContainer AnimationTags;

	/*
	 *	Указатель на твой кастомный персонаж, чтобы получить из него GAS.
	 *	В принципе, можно обойтись и без него если есть другой способ достать указатель на GAS.
	 *	В любом случае, лишним не будет.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GGE2D")
	TObjectPtr<AOmegaCharacter> SourceCharacter;

	/*
	 *	Собственно сама GAS.
	 *	Нужна, чтобы получить доступ к встроенному делегату RegisterGameplayTagEvent, который будет срабатывать каждый раз когда на GAS будет накладываться
	 *	тэг передвижения. Здесь для демонстрации 3 тега: Animation_Death, Animation_Dash и Animation_Attack. 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GGE2D")
	TObjectPtr<UOmegaAbilitySystemComponent> SourceASC;

public:
	
	/*
	 * Функция пытается присвоить в переменные SourceCharacter и SourceASC персонажа-владельца и его GAS, если есть.*
	 * Если хотя бы один из этих параметров будет пустым - вернет false.
	 * Если все ок - вернет true
	 * Предполагается, что будет запускаться в OnInit.
	 */
	bool GetEssentials();

	
	virtual void OnInit_Implementation() override;
	virtual void OnTick_Implementation(float DeltaTime) override;

	/*
	 * Функция решает добавить или удалить тег из контейнера в зависимости от значения передаваемого делегатом RegisterGameplayTagEvent
	 */
	UFUNCTION()
	void UpdateAnimationTags(const FGameplayTag& InGameplayTag, int32 StackCount);
};


