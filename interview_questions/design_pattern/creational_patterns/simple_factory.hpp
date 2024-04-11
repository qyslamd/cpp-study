#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <memory>

namespace simple_factory_demo {

class XiaoMi_Su7 {
 public:
  XiaoMi_Su7(const std::string& name) : name(name){}
  virtual ~XiaoMi_Su7() {}
  enum DriveMode {
    FrontWheelDrive, RearWheelDrive, FourWheelDrive
  };
  virtual DriveMode GetDriveMode() const = 0;
  virtual float _0_100km_time() const = 0;
  virtual float CLTC_ratedRange() const = 0;
  virtual float maximunSpeed() const = 0;

  void show() const {
    auto mode = GetDriveMode();
    auto _0_100 = _0_100km_time();
    auto cltc = CLTC_ratedRange();
    auto maxSpeed = maximunSpeed();

    std::stringstream ss;
    ss << "This is " << name << " " << std::endl;
    ss << "dirvemode"
       << "\t"
       << "0~100km time"
       << "\t"
       << "CLTC range"
       << "\t"
       << "maximun speed" << std::endl;
    switch (mode) {
      case simple_factory_demo::XiaoMi_Su7::FrontWheelDrive:
      case simple_factory_demo::XiaoMi_Su7::RearWheelDrive:
        ss << "前置后驱";
        break;
      case simple_factory_demo::XiaoMi_Su7::FourWheelDrive:
        ss << "双电机四驱";
        break;
      default:
        break;
    }
    ss << "\t" << _0_100
       << "\t" << cltc
       << "\t" << maxSpeed << std::endl;

    std::cout << ss.str() << std::endl;
  }

 protected:
  std::string name;
};

class XiaoMi_Su7_Standard :public XiaoMi_Su7 {
 public:
  XiaoMi_Su7_Standard() : XiaoMi_Su7("XiaoMi_Su7_Standard") {}
  DriveMode GetDriveMode() const override { return RearWheelDrive; }
  float _0_100km_time() const override { return 5.28; }
  float CLTC_ratedRange() const override { return 700; }
  float maximunSpeed() const override { return 210; }
};

class XiaoMi_Su7_Pro : public XiaoMi_Su7 {
 public:
  XiaoMi_Su7_Pro() : XiaoMi_Su7("XiaoMi_Su7_Pro") {}
  DriveMode GetDriveMode() const override { return RearWheelDrive; }
  float _0_100km_time() const override { return 5.7; }
  float CLTC_ratedRange() const override { return 830; }
  float maximunSpeed() const override { return 210; }
};

class XiaoMi_Su7_Max : public XiaoMi_Su7 {
 public:
  XiaoMi_Su7_Max() : XiaoMi_Su7("XiaoMi_Su7_Max") {}
  DriveMode GetDriveMode() const override { return FourWheelDrive; }
  float _0_100km_time() const override { return 2.78; }
  float CLTC_ratedRange() const override { return 800; }
  float maximunSpeed() const override { return 265; }
};

class BeiJingFactory {
 public:
  enum SeriesType {Standard, Pro, Max};
  XiaoMi_Su7* produceSu7(SeriesType type) {
    switch (type) {
      case simple_factory_demo::BeiJingFactory::Standard:
        return new XiaoMi_Su7_Standard();
        break;
      case simple_factory_demo::BeiJingFactory::Pro:
        return new XiaoMi_Su7_Pro();
        break;
      case simple_factory_demo::BeiJingFactory::Max:
        return new XiaoMi_Su7_Max();
        break;
      default:
        break;
    }
    return nullptr;
  }
};

struct Client {
    void operator()() {
    BeiJingFactory factory;
    std::shared_ptr<XiaoMi_Su7> standard(
        factory.produceSu7(simple_factory_demo::BeiJingFactory::Standard));
    standard->show();

    std::shared_ptr<XiaoMi_Su7> pro(
        factory.produceSu7(simple_factory_demo::BeiJingFactory::Pro));
    pro->show();

    std::shared_ptr<XiaoMi_Su7> max(
        factory.produceSu7(simple_factory_demo::BeiJingFactory::Max));
    max->show();
  }

    static void test() {
    Client client;
    client();
  }
};
}  // namespace simple_factory_demo