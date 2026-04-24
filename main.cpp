#include <bits/stdc++.h>
using namespace std;

namespace LIST {

struct NODE {
    int val;
    NODE* prev;
    NODE* next;
};

static NODE* head = nullptr;
static NODE* tail = nullptr;
static int len = 0;

void Pre() {
    head = tail = nullptr;
    len = 0;
}

// Move to node at index i (0-based). Assumes 0 <= i < len.
static NODE* move_to(int i) {
    if (i < 0 || i >= len) return nullptr;
    // choose direction for efficiency
    if (i < len / 2) {
        NODE* cur = head;
        for (int k = 0; k < i; ++k) cur = cur->next;
        return cur;
    } else {
        NODE* cur = tail;
        for (int k = len - 1; k > i; --k) cur = cur->prev;
        return cur;
    }
}

void insert(int i, int x) {
    // insert value x so that it ends up at index i
    NODE* node = new NODE{ x, nullptr, nullptr };
    if (len == 0) {
        head = tail = node;
        len = 1;
        return;
    }
    if (i <= 0) {
        // insert at front
        node->next = head;
        head->prev = node;
        head = node;
        ++len;
        return;
    }
    if (i >= len) {
        // insert at back
        node->prev = tail;
        tail->next = node;
        tail = node;
        ++len;
        return;
    }
    // insert before node at index i
    NODE* pos = move_to(i);
    node->next = pos;
    node->prev = pos->prev;
    if (pos->prev) pos->prev->next = node;
    pos->prev = node;
    if (i == 0) head = node; // safety, though handled above
    ++len;
}

void remove(int i) {
    if (len == 0 || i < 0 || i >= len) return; // input guarantees valid, but be safe
    NODE* target = move_to(i);
    NODE* p = target->prev;
    NODE* n = target->next;
    if (p) p->next = n; else head = n;
    if (n) n->prev = p; else tail = p;
    delete target;
    --len;
}

int Get_length() { return len; }

int Query(int i) {
    if (i < 0 || i >= len) return -1;
    NODE* target = move_to(i);
    return target ? target->val : -1;
}

void Print() {
    if (len == 0) {
        cout << -1 << '\n';
        return;
    }
    NODE* cur = head;
    bool first = true;
    while (cur) {
        if (!first) cout << ' ';
        cout << cur->val;
        first = false;
        cur = cur->next;
    }
    cout << '\n';
}

void Clear() {
    NODE* cur = head;
    while (cur) {
        NODE* n = cur->next;
        delete cur;
        cur = n;
    }
    head = tail = nullptr;
    len = 0;
}

} // namespace LIST

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int op, x, p, ans;
    LIST::Pre();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                ans = LIST::Get_length();
                cout << ans << '\n';
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << '\n';
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
            default:
                break;
        }
    }
    LIST::Clear();
    return 0;
}

