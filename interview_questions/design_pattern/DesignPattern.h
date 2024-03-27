#pragma once

#include <iostream>
#include <string>

namespace design_patterns {

/*
 * see https://refactoringguru.cn/design-patterns/cpp
 */
void execute();

struct SOLID {
  static void description();

  /// <summary>
  /// Single Responsibility Principle
  /// ��һְ��ԭ��
  /// </summary>
  static std::string SRP();

  /// <summary>
  /// Open-Closed Principle
  /// ����ԭ��
  /// </summary>
  static std::string OCP();
  /// <summary>
  /// Liskov Substitution Principle
  /// �����滻ԭ��
  /// </summary>
  static std::string LSP();

  /// <summary>
  /// Interface Segregation Principle
  /// �ӿڸ���ԭ��
  /// </summary>
  static std::string ISP();

  /// <summary>
  /// Dependency Inversion/Injection
  /// ��������/ע��
  /// </summary>
  static std::string DI();
};

struct CreationalPatterns {
  static auto abstractFactory() -> void;
  static auto factoryMethod() -> void;
  static auto builder() -> void;
  static auto prototype() -> void;
  static auto singleton() -> void;
};

}  // namespace design_patterns