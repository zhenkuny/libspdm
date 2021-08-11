
int main() {

  unsigned char buffer[100];
  __ESBMC_init_var(buffer);

  run_test_harness((void*)buffer, 100);
  return 0;
}