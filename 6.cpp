#include <stdexcept>
#include <vector>

using namespace std;

class Tower {
public:
    Tower(int disks_num) {
        FillTower(disks_num);
    }

    [[nodiscard]] int GetDisksNum() const {
        return disks_.size();
    }

    void SetDisks(int disks_num) {
        FillTower(disks_num);
    }

    void AddToTop(int disk) {
        int top_disk_num = disks_.size() - 1;
        if (0 != disks_.size() && disk >= disks_[top_disk_num]) {
            throw invalid_argument("Невозможно поместить большой диск на маленький");
        } else {
            disks_.push_back(disk);
        }
    }

    void DeleteDisk() {
        disks_.pop_back();
    }

    int GetHeadOfTower() {
        return disks_.back();
    }

private:
    vector<int> disks_;

    void FillTower(int disks_num) {
        for (int i = disks_num; i > 0; i--) {
            disks_.push_back(i);
        }
    }
};

void MoveDisks(int disks_num, Tower &source_tower, Tower &temp_tower, Tower &need_tower) {
    if (disks_num == 0) {
        return;
    }
    MoveDisks(disks_num - 1, source_tower, need_tower, temp_tower);
    need_tower.AddToTop(source_tower.GetHeadOfTower());
    source_tower.DeleteDisk();
    MoveDisks(disks_num - 1, temp_tower, source_tower, need_tower);
}

void SolveHanoi(vector<Tower> &towers) {
    int disks_num = towers[0].GetDisksNum();
    MoveDisks(disks_num, towers[0], towers[1], towers[2]);
}

int main() {
    int towers_num = 3;
    int disks_num = 3;
    vector<Tower> towers;
    for (int i = 0; i < towers_num; ++i) {
        towers.push_back(0);
    }
    towers[0].SetDisks(disks_num);

    SolveHanoi(towers);
}