#pragma once

#include <iostream>
#include <string>

namespace design_patterns {
void execute();

struct SOLID {
  static void description();

  /// <summary>
  /// Single Responsibility Principle
  /// 单一职责原则
  /// </summary>
  static std::string SRP();

  /// <summary>
  /// Open-Closed Principle
  /// 开闭原则
  /// </summary>
  static std::string OCP();
  /// <summary>
  /// Liskov Substitution Principle
  /// 里氏替换原则
  /// </summary>
  static std::string LSP();

  /// <summary>
  /// Interface Segregation Principle
  /// 接口隔离原则
  /// </summary>
  static std::string ISP();

  /// <summary>
  /// Dependency Inversion/Injection
  /// 依赖倒置/注入
  /// </summary>
  static std::string DI();
};

}  // namespace design_patterns