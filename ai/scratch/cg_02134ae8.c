extern double func_021400ec(double x, int *exp);
extern double func_021401ac(double value, int exp);

double Maybe_helper_134ae8(double x, int n) {
    double value;
    int exp;

    value = func_021400ec(x, &exp);
    exp += n;

    return func_021401ac(value, exp);
}
