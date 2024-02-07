#pragma once

#include "ptrvector.h"
#include "scopedptr.h"
#include <new>
#include <vector>

// Щупальце
class Tentacle {
public:
    explicit Tentacle(int id) noexcept
            : id_(id) {
    }


    int GetId() const noexcept {
        return id_;
    }

    Tentacle *GetLinkedTentacle() const noexcept {
        return linked_tentacle_;
    }

    void LinkTo(Tentacle &tentacle) noexcept {
        linked_tentacle_ = &tentacle;
    }

    void Unlink() noexcept {
        linked_tentacle_ = nullptr;
    }

private:
    int id_ = 0;
    Tentacle *linked_tentacle_ = nullptr;
};

// Осьминог
class Octopus {
public:
    Octopus()
            : Octopus(8) {
    }

    explicit Octopus(int num_tentacles) {
        for (int i = 0; i < num_tentacles; ++i) {
            ScopedPtr<Tentacle> ptr(new Tentacle(i + 1));
            tentacles_.GetItems().push_back(ptr.GetRawPtr());
            ptr.Release();
        }
    }

    // Добавляет новое щупальце с идентификатором,
    // равным (количество_щупалец + 1):
    // 1, 2, 3, ...
    // Возвращает ссылку на добавленное щупальце
    Tentacle& AddTentacle(){
        ScopedPtr<Tentacle> n_tentacle(new Tentacle(GetTentacleCount() + 1));
        tentacles_.GetItems().push_back(n_tentacle.GetRawPtr());
        n_tentacle.Release();
        return *tentacles_.GetItems().back();
    }


    int GetTentacleCount() const noexcept {
        return tentacles_.GetItems().size();
    }

    const Tentacle &GetTentacle(size_t index) const {
        return *tentacles_.GetItems().at(index);
    }

    Tentacle &GetTentacle(size_t index) {
        return *tentacles_.GetItems().at(index);
    }

private:
    // Вектор хранит указатели на щупальца. Сами объекты щупалец находятся в куче
    PtrVector<Tentacle> tentacles_;
};