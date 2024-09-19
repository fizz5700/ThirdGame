
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlashHUD.generated.h"

class USlashOverlay;
/**
 * 
 */
UCLASS()
class THIRDGAME_API ASlashHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Slash")
	TSubclassOf<USlashOverlay> SlashOverlayClass;

	

	UFUNCTION(BlueprintCallable)
	void InitializationHud();
public:
	UPROPERTY(BlueprintReadWrite)
	USlashOverlay* SlashOverlay;
	FORCEINLINE USlashOverlay* GetSlashOverlay() const { return SlashOverlay; }

};
