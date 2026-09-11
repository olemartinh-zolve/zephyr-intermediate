#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

#define PRIO_T_LOW 7
#define PRIO_T_MED 5
#define PRIO_T_HIGH 3
#define PRIO_T_COOP -1

void t_low_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_LOW running");
        k_msleep(300);
    }
}

void t_med_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_MED running");
        k_msleep(200);
    }
}

void t_high_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_HIGH running");
        k_msleep(100);
    }
}

void t_coop_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        for (int i = 0; i < 5; i++) {
            LOG_INF("T_COOP running");
            k_busy_wait(50000);
        }
        LOG_INF("T_COOP yields");
        // Exercise instructs to yield. It will immediately start again (and block other threads)
        // since all other threads have lower priority.
        k_yield();
    }
}

K_THREAD_DEFINE(t_low, STACK_SIZE, t_low_fn,NULL, NULL, NULL, PRIO_T_LOW, 0, 0);
K_THREAD_DEFINE(t_med, STACK_SIZE, t_med_fn,NULL, NULL, NULL, PRIO_T_MED, 0, 0);
K_THREAD_DEFINE(t_high, STACK_SIZE, t_high_fn,NULL, NULL, NULL, PRIO_T_HIGH, 0, 0);
K_THREAD_DEFINE(t_coop, STACK_SIZE, t_coop_fn,NULL, NULL, NULL, PRIO_T_COOP, 0, 0);

int main(void)
{
    return 0;
}

