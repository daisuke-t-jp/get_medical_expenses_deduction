/**
 * 医療費控除を計算する
 *
 * refs:
 * - https://www.nta.go.jp/taxes/shiraberu/taxanswer/shotoku/1120.htm
 * - https://www.nta.go.jp/publication/pamph/pdf/iryoukoujyo_meisai.pdf
 */

#include <stdio.h>
#include <math.h>
#include <assert.h>

static int get_medical_expenses_deduction(int payed, int insurance, int income);

int main(int argc, const char * argv[]) {
  assert(get_medical_expenses_deduction(200000, 0, 3000000) == 100000);
  assert(get_medical_expenses_deduction(200000, 50000, 3000000) == 50000);
  assert(get_medical_expenses_deduction(1000000, 0, 3000000) == 900000);
  assert(get_medical_expenses_deduction(1000000, 0, 1000000) == 950000);
  assert(get_medical_expenses_deduction(1000000, 0, 0) == 1000000);

  return 0;
}


/**
 * 医療費控除額を得る
 *
 * @param payed その年に支払った医療費
 * @param insurance 保険金などで補填される金額（生命保険など）
 * @param income その年に得た総所得
 *
 * @return 医療費控除額
 */
static int get_medical_expenses_deduction(int payed, int insurance, int income) {
  static const double income_coe = 0.05;    // 総所得にかける係数
  static const int income_border = 2000000; // 総所得の閾値
  static const int default_val2 = 100000;   // 控除から引くデフォルトの値
  static const int deduction_max = 2000000; // 控除の最高額
  
  
  // 基本となる控除額を算出する
  int val = payed - insurance;
  if(val < 0) {
    val = 0;
  }
  
  
  // 控除から引く額を算出する
  int val2 = default_val2;
  if(income < income_border) {
    // 総所得が閾値未満
    // -> 総所得に係数をかけた額を使用する
    val2 = ceil(income * income_coe);
  }
  
  
  // 控除額を計算する
  int deduction = val - val2;
  if(deduction > deduction_max) {
    deduction = deduction_max;
  }
  if(deduction < 0) {
    deduction = 0;
  }
  
  return deduction;
}
