import { MainPage } from '@harmony-lib/netkit'

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  build() {
    RelativeContainer() {
      MainPage()
    }
    .height('100%')
    .width('100%')
  }
}