#include "core/core.h"

int main() {
	Window window;

	do {
		window.Clear();
		window.Update();
	} while (!window.Closed());
}
