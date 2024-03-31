#pragma once

#include <iostream>
#include <string>
#include <memory>

namespace bridge_demo {
/*
* 桥接模式应用场景：
* 1.如果想要拆分或者重组一个具有多重功能的庞杂类，可以使用桥接模式
* 2.如果希望在几个独立维度上扩展一个类，可以使用该模式
* 3.如果希望在运行时切换不同的实现方法，可以使用该模式
*/


/// <summary>
/// 基本示例
/// </summary>
struct Implementation {
  virtual ~Implementation(){};
  virtual std::string OperationImplementation() const = 0;
};
struct ConcreteImplementationA : public Implementation {
  std::string OperationImplementation() const override {
    return "Concrete implementation A, Here's result of platformA.";
  }
};

struct ConcreteImplementationB : public Implementation {
  std::string OperationImplementation() const override {
    return "Concrete implementation B, Here's result of platformB.";
  }
};

struct Abstraction {
  Abstraction(std::shared_ptr<Implementation> implementation)
      : implementation(implementation) {}
  virtual ~Abstraction() {}

  virtual std::string Operation() const {
    return "abstraction operate with:\n" +
           implementation->OperationImplementation();
  }

 protected:
  std::shared_ptr<Implementation> implementation;
};

struct ExtendAbstraction : Abstraction {
  ExtendAbstraction(std::shared_ptr<Implementation> imp) : Abstraction(imp) {}

  std::string Operation() const override {
    return "ExtendAbstraction: extended operation with:\n" +
           implementation->OperationImplementation();
  }
};

/// <summary>
/// 另一个示例
/// </summary>
struct MediaFormat {
  virtual ~MediaFormat() {}
  virtual void play() = 0;
};
struct MediaPlayer {
  MediaPlayer(std::shared_ptr<MediaFormat> format) : m_format(format) {}
  virtual ~MediaPlayer() {}
  virtual void play() = 0;

 protected:
  std::shared_ptr<MediaFormat> m_format;
};

struct MP3Format : MediaFormat {
  virtual void play() { std::cout << "Playing MP3 format." << std::endl; }
};
struct MP4Format : MediaFormat {
  virtual void play() { std::cout << "Playing MP4 format." << std::endl; }
};
struct AVIFormat : MediaFormat {
  virtual void play() { std::cout << "Playing AVI format." << std::endl; }
};

struct AudioPlayer : MediaPlayer {
  AudioPlayer(std::shared_ptr<MediaFormat> format) : MediaPlayer(format) {}
  virtual void play() { m_format->play(); }
};

struct Client {
  void operator()(const Abstraction& abs) {
    std::cout << abs.Operation() << std::endl;
  }
};

struct Client2 {
  void operator()(MediaPlayer& player) { player.play(); }
};
struct App {
  static void execute() {
    // none-specific sense demo.
    std::shared_ptr<Implementation> impl =
        std::make_shared<ConcreteImplementationA>();
    std::shared_ptr<Abstraction> abs =
        std::make_shared<ExtendAbstraction>(impl);
    Client client;
    client(*abs);
    std::cout << std::endl;

    // player demo.
    Client2 client2;
    std::shared_ptr<MediaFormat> mp3_format = std::make_shared<MP3Format>();
    std::shared_ptr<MediaPlayer> player1 =
        std::make_shared<AudioPlayer>(mp3_format);
    client2(*player1);

    std::shared_ptr<MediaFormat> mp4_format = std::make_shared<MP4Format>();
    std::shared_ptr<MediaPlayer> player2 =
        std::make_shared<AudioPlayer>(mp3_format);
    client2(*player2);

    std::shared_ptr<MediaFormat> avi_format = std::make_shared<AVIFormat>();
    std::shared_ptr<MediaPlayer> player3 =
        std::make_shared<AudioPlayer>(avi_format);
    client2(*player3);
  }
};
}  // namespace bridge_demo