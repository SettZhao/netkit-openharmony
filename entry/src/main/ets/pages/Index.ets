import { getAllByName, getByName, getHostName } from '@harmony-lib/netkit';
import { hilog } from '@kit.PerformanceAnalysisKit';

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  build() {
    RelativeContainer() {
      Text(this.message)
        .id('HelloWorld')
        .fontSize($r('app.float.page_text_font_size'))
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })
        .onClick(() => {
          const DOMAIN = 0x0000;
          this.message = 'Welcome';
          hilog.info(DOMAIN, 'testTag', 'getByName for www.baidu.com: %{public}s', getByName("www.baidu.com"));
          hilog.info(DOMAIN, 'testTag', 'getAllByName for www.baidu.com: %{public}s', JSON.stringify(getAllByName("www.baidu.com")));
          hilog.info(DOMAIN, 'testTag', 'getHostName for 8.8.8.8: %{public}s', JSON.stringify(getHostName("8.8.8.8")));

        })
    }
    .height('100%')
    .width('100%')
  }
}