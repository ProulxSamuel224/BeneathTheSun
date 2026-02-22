#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "ACorridor.generated.h"

UCLASS()
class BTS_API AACorridor : public AActor
{
	GENERATED_BODY()
	
public:
	// Définit les valeurs par défaut des propriétés de ce actor
	AACorridor();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline", AdvancedDisplay)
	TSubclassOf<AActor> SplineActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline", AdvancedDisplay)
	FVector SplineOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", AdvancedDisplay)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", AdvancedDisplay)
	TArray<UMaterialInterface*> MaterialList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", AdvancedDisplay)
	FVector EnemyLocationOffset = FVector::ZeroVector;

	UPROPERTY(Transient)
	AActor* RuntimeSplineActor = nullptr;

	int8 MaterialIndex = 0;

	UWorld* World = nullptr;

protected:
	// Appelé au début du jeu ou au moment de l'apparition de l'animal.
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddActorToCorridor(AActor* InActor);

	UStaticMeshComponent* GetMesh() { return StaticMesh; }

	void SetMaterialIndex(int8 index) { MaterialIndex = index; }

	USplineComponent* GetSplineFromCorridor();

	UFUNCTION(BlueprintCallable)
	const FVector GetCorridorEndLocation() { return CorridorEndLocation; }
	UFUNCTION(BlueprintCallable)
	const FVector GetCorridorStartLocation() { return CorridorStartLocation; }
	
	UFUNCTION(BlueprintCallable)
	const FVector GetEnemySpawnLocation() { return GetActorLocation() + EnemyLocationOffset; }

	UFUNCTION(BlueprintCallable)
	bool IsOccupiedByEnemy() const { return bIsOccupiedByEnemy; }

	UFUNCTION(BlueprintCallable)
	void SetIsOccupiedByEnemy(bool bOccupied) { bIsOccupiedByEnemy = bOccupied; }

	UFUNCTION(BlueprintImplementableEvent)
	void OnCorridorTargetted();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCorridorUnTargetted();
private:

	 FVector CorridorStartLocation;

	 FVector CorridorEndLocation;

	 bool bIsOccupiedByEnemy = false;
};
