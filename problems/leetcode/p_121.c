int maxProfit(int *prices, int pricesSize) {
  int buy_price, max_profit = 0, current_profit;

  // Day1 초기값 세팅
  buy_price = prices[0];

  for (int i = 1; i < pricesSize; i++) {
    // 기존 buy_price 보다 현재 가격이 더 낮으면 구매
    if (prices[i] < buy_price) {
      buy_price = prices[i];
    }

    current_profit = prices[i] - buy_price;
    // 기존 max_profit 보다 더 차이가 큰 경우 판매가 개신
    if (current_profit > max_profit) {
      max_profit = current_profit;
    }
  }

  return max_profit;
}

int main(void) {
}
