#include <xenos/xe.h>
#include <console/console.h>
#include <debug.h>
#include <xenon_uart/xenon_uart.h>
#include <xenon_soc/xenon_power.h>
#include <time/time.h>

int main() {
    // Инициализация отладки
    xenon_uart_init();
    console_init();
    xenos_init(VIDEO_MODE_AUTO);
    console_close();

    // Настройка экрана
    struct XenosSurface *fb = NULL;
    fb = xenos_create_surface(640, 480, XE_FMT_8888 | XE_SURFACE_NO_TEXTURE);

    u32 white = 0xFFFFFFFF;
    u32 black = 0x00000000;
    u32 *pixels = (u32 *)fb->base;

    int toggle = 0;

    for (;;) {
        u32 color = toggle ? white : black;
        for (int i = 0; i < fb->width * fb->height; i++) {
            pixels[i] = color;
        }

        xenos_present(fb);
        toggle = !toggle;
        udelay(500000); // 500 мс
    }

    return 0;
}
