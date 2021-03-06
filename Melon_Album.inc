# Mp3tag parsing for Melon.com
#
# Created by HyunKyun Moon
#
# Save it in your Mp3tag data directory, i.e.
# %APPDATA%\Mp3tag\data\sources
#

[ParserScriptAlbum]=...

# check
# 정규 => 10056666
# 여러가수 => 332407
# Digital Single => 10210535
# Various Artist => 나가수(2170909), 로필2012(2139099)
# cd 1,2 => 2222589


# check
# 아티스트, 앨범, 연도, 장르, 트랙

OutputTo "CoverURL"
FindLine "<div class=\"wrap_info\">"
FindLine "<img"
FindInLine "src=\""
SayUntil ".jpg"
Say ".jpg"

OutputTo "ALBUM"
FindLine "<div class=\"song_name\">"
JoinUntil "</div>"
RegexpReplace "<strong.+strong>" ""
RegexpReplace "<[^>]+>" ""
SayRest

OutputTo "AlbumArtist"
FindLine "<div class=\"artist\">"
JoinUntil "</div>"
RegexpReplace "<[^>]+>" ""
SayRest

OutputTo "YEAR"
FindLine "<dt>발매일</dt>"
FindLine "<dd>"
FindInLine "<dd>"
SayUntil "</dd>"

OutputTo "GENRE"
FindLine "<dt>장르</dt>"
FindLine "<dd>"
FindInLine "<dd>"
SayUntil "</dd>"

# OutputTo "추가"
# Say "정보"

FindLine "<tbody>"
Do
    OutputTo "tCD"
    FindLine "<tr data-group-items"
    FindInLine "=\""
    SayUntil "\""
    Say "|"

    OutputTo "tTrack"
    FindLine "<span class=\"rank"
    RegexpReplace "<span class=\"none\">.+</span>" ""
    RegexpReplace "<[^>]+>" ""
    SayRest
    Say "|"


    FindLine "<div class=\"ellipsis\">"
    MoveLine +1
    FindLine "<" 1 1
    Unspace

    OutputTo "tTrackTitle"
    If "<span title="
        MoveLine +1
        FindLine "<" 1 1
        Unspace
        Say "O"
    Else
        Say ""
    Endif
    Say "|"

    OutputTo "tTracks"
    If "<span class=\"disabled"
        Unspace
    Else
        FindLine "<a href"
    Endif
    RegexpReplace "<[^>]+>" ""
    SayRest
    Say "|"

    OutputTo "tArtist"
    FindLine "<div class=\"ellipsis rank02\">"
    JoinUntil "</div>"
    # FindInLine ">"
    # "<a>abc</a>, <a>def</a><span><a>ghi</a>, <a>jkl</a></span>"
    # "<a>abc</a>, <a>def</a>"
    RegexpReplace "<span(.+)</span>" ""
    RegexpReplace "<[^>]+>" ""
    SayRest
    Say "|"

    JoinUntil "</tr>"
    MoveLine +1
    FindLine "<"
    Unspace

    If "<tr class=\"cd\">"
        JoinUntil "</tr>"
        MoveLine +1
        FindLine "<"
        Unspace
    Endif
While "<tr data-group-items="

# OutputTo "COMMENT"
# FindLine "<div class=\"dtl_album"
# MoveLine +1
# # RegexpReplace "<br>" "\n"
# RegexpReplace "<[^>]+>" ""
# SayRest
# Say "<div><div>	<div>		<strong><span style=\"color:#ff0000;\">*사랑이 잘 (With 오혁), 밤편지는 싱글 [사랑이 잘]과 [밤편지]에서 감상하실 수 있습니다.</span><br>		<br>		작은 순간순간을 예쁜 물감으로 만들어, '아이유'의 '이 지금'을 빼곡히 채워내다.</strong></div></div><div>	<strong>'아이유(IU)' 정규4집 [Palette] 전격 발매!</strong></div><div>	&nbsp;</div><div>	'아이유(IU)'의 네 번째 정규앨범 [Palette]가 드디어 공개됐다.</div><div>	&nbsp;</div><div>	'아이유'는 지난달 24일 발표한 첫 선공개곡 \"밤편지\"를 시작으로 동갑내기 뮤지션 '오혁'과 함께 한 두 번째 선공개곡 \"사랑이 잘\"까지, 연달아 '퍼펙트 올킬' 기록을 세우며 그 이름값을 톡톡히 지켜 냈다.</div><div>	&nbsp;</div><div>	'아이유'가 1년 반 만에 꺼내 놓은 신보이자 정규앨범으로는 3년 여만인 정규 4집 앨범 [Palette]는, 미리 발표된 두 선공개곡을 통해 짐작할 수 있듯이 특정 장르나 스타일에 제한하지 않고 다채로운 음악색과 이야기를 한데 담아낸, 앨범명 의미 그대로의 '팔레트'와 같은 앨범이다.</div><div>	&nbsp;</div><div>	'아이유'의 정규4집 [Palette]는 '아이유' 본인이 직접 프로듀싱을 맡아 긴 호흡으로 공들여 작업한 만큼 가수 '아이유'의 또 다른 변신과 프로듀서 '아이유'의 음악적 성장을 새롭게 발견할 수 있게 한다. 또한, 그는 이번 앨범에서 '이병우', '손성제', 'G-DRAGON', '선우정아', '오혁', '샘 김' 등 세대와 장르를 아우르는 최고의 뮤지션들과 만나 음악적 스펙트럼을 넓히는 동시에, 특유의 섬세한 음색과 노랫말로 모든 넘버를 '아이유' 만의 감성으로 색칠하며, 도무지 그 음악적 한계와 컬러를 단정지을 수 없게 한다.</div><div>	&nbsp;</div><div>	\"내가 머릿속으로 그렸던 꿈이 현실이 되어 눈 앞에 펼쳐지는 순간</div><div>	저의 팔레트는 또 한 칸 새로운 물감으로 채워집니다…</div><div>	지금 이 순간도 언젠가 내가 정성스럽게 그렸었던 꿈이죠</div><div>	오늘 이 순간을 예쁜 물감으로 만들어 나는 또 꿈을 그릴 겁니다\"</div><div>	- 2016 '아이유' 콘서트 '하나 둘 셋 넷'-</div><div>	&nbsp;</div><div>	데뷔 10년차 아티스트 혹은 스물다섯 살 '이지은'의 작은 순간순간이 예쁜 물감이 되어 차곡히 채워진 '아이유'의 '이 지금', 새하얀 '팔레트'에 그녀가 새롭게 배합해 낸 이 음악, 이 물감으로 어떤 그림을 완성할지는 오랜 시간 그녀의 새 앨범을 기다려온 청중의 몫으로 남겨두고자 한다.</div><div>	&nbsp;</div><div>	[TRACK REVIEW]</div><div>	&nbsp;</div><div>	01. 이 지금</div><div>	Composed by 김제휘 / Lyrics by 아이유 / Arranged by 김제휘</div><div>	화려한 코드진행이 돋보이는 기분 좋은 팝재즈 트랙으로 \"밤편지\", \"마음\" 등 수 차례 '아이유'와 멋진 호흡을 보여준 '김제휘'가 작곡을, '아이유'가 작사를 맡았다. 깜짝 놀랄 만큼 빛이 나고 아름다운 건 다른 어느 것도 아닌 바로 지금, 여기, 우리라는 메시지가 사랑스럽게 다가오는 곡이다.</div><div>	&nbsp;</div><div>	02. 팔레트 (Feat. G-DRAGON) *TITLE</div><div>	Composed by 아이유 / Lyrics by 아이유 / Arranged by 이종훈 / Rap Making by G-DRAGON</div><div>	'아이유'가 기존에 시도해보지 않은 장르의 감각적이면서도 포근한 신스팝 R&amp;B 트랙이다. 2년 전에 발매했던 \"스물셋\"과는 다른 듯, 또 이어지는 '아이유' 본인에 대한 이야기를 차분히 담아내고 있다. \"스물셋\"에서는 동시에 함께 존재하는 전혀 다른 이면과 그 혼란스러움을 솔직하고 대담하게 풀어놨다면 이번에는 헷갈리지 않고 본인이 좋아하는 것을 또박또박 짚어내며 \"이제 날 조금 알 것 같다\"고 이야기하는 '아이유'의 여유가 돋보인다. 더욱이 'G-DRAGON'의 피쳐링으로 이 이야기는 단순히 '아이유' 개인만의 것이 아닌 스물다섯이라는 나이, 또는 청춘이 가지는 그 아름다움과 찬란함으로 주제가 확장된다. 진솔하면서도 날이 서지 않은 다정한 메시지가 부드러운 신스소리와 어우러져 살랑거린다.</div><div>	&nbsp;</div><div>	03. 이런 엔딩</div><div>	Composed by 샘 김 / Lyrics by 아이유 / Arranged by 이종훈</div><div>	빈티지한 피아노 소리와 서정적인 오케스트라 선율이 완벽한 하모니를 자랑하는 R&amp;B 발라드 트랙이다. 감성과 감각을 동시에 표현해내는 천재 아티스트 '샘 김'의 곡과 '아이유'의 가사와 보컬이 만나 전혀 새로운 색깔을 만들어낸다. 이별을 겪은 남녀라면 쉽게 공감할 만한, 사랑에 있어 가장 슬픈 이별의 순간을 둘이 만든 영화의 엔딩씬으로 빗대어 가사로 풀어낸 곡이다.</div><div>	&nbsp;</div><div>	04. 사랑이 잘 (With 오혁)</div><div>	Composed by 이종훈, 아이유, 오혁 / Lyrics by 아이유, 오혁 / Arranged by 이종훈</div><div>	'아이유'와 '오혁'의 공식적인 첫 콜라보레이션으로 정규4집의 두 번째 선공개곡으로 낙점, 두 아티스트의 색다른 매력과 독특한 케미로 발매 전부터 대중의 큰 관심을 받았다. 미니멀한 악기 구성의 R&amp;B 넘버인 이 곡에서 '아이유'와 '오혁'은, 직접 작사, 작곡에 참여하였고, 현실적이면서도 감각적인 가사와 멜로디를 주고 받으며 권태기 남녀의 갈등을 긴장감 있게 표현해 냈으며, Track Producer로는 데뷔곡 \"미아\"부터 \"봄, 사랑, 벚꽃 말고\", \"레옹\", \"스물셋\" 등을 함께해온 작곡가 '이종훈'이 참여해 곡의 완성도를 더했다.</div><div>	&nbsp;</div><div>	05. 잼잼</div><div>	Composed by 선우정아 / Lyrics by 선우정아, 아이유 / Arranged by 선우정아, 윤석철</div><div>	농담을 건네듯 재기 발랄한 사운드의 일렉트로닉 신스팝 트랙이다. \"봄처녀\", \"순이\", \"비온다\" 등 색깔이 뚜렷한 음악으로 모든 뮤지션들이 탐내는 매력적인 아티스트 '선우정아'가 작곡가로 나섰고 '아이유'와 '선우정아'가 함께 글을 작업했다. 사랑에 대한 냉소적이고도 사실은 애절한 고찰이 눈길을 끄는 곡이다.</div><div>	&nbsp;</div><div>	06. Black Out</div><div>	Composed by 이종훈 / Lyrics by 아이유 / Arranged by 이종훈</div><div>	제목에서도 눈치 챌 수 있듯 술 냄새가 강하게 풍기는 인디팝 트랙이다. 장난스러운 베이스와 리듬과는 전혀 상반되는 진지한 기타 솔로가 아이러닉하면서도 매력적인 킬링 파트가 된다. 기본적으로는 헛소리인 듯하지만 모두들 각자 취했을 때를 생각해 보면.. '휴 더 하면 더 했지..'</div><div>	&nbsp;</div><div>	07. 마침표</div><div>	Composed by 손성제 / Lyrics by 아이유 / Arranged by 손성제</div><div>	피아노, 스트링, 플룻, 클라리넷의 신선한 구성의 발라드 트랙이다. 처음부터 끝까지 정해진 BPM 없이 연주자와 보컬이 프리하게 곡을 끌고 나간다는 점 또한 눈에 띈다. 재즈신에서 이미 수준 높은 음악성으로 정평이 나 있는 섬세한 아티스트 '손성제'가 작곡가로 나섰다. 갑자기 뽑혀나간 사랑니 자리를 오래도록 앓듯, 아직 마음은 아프더라도 이제는 정말 마침표를 찍겠다는 다짐이, 그럼에도 누구 하나 울부짖지 않는 절제된 소리들이 더욱 서글프게 다가온다.</div><div>	&nbsp;</div><div>	08. 밤편지</div><div>	Composed by 김제휘, 김희원 / Lyrics by 아이유 / Arranged by 김제휘, 김희원</div><div>	서정적인 기타 선율과 '아이유'의 목소리가 잘 어우러진 어쿠스틱 사운드의 포크 발라드로, 작곡에는 \"마음\"과 \"나의 옛날 이야기\" 등으로 이미 수 차례 '아이유'와 공동작업을 맡았던 작곡가 '김제휘'와 뉴페이스 '김희원'이, 작사에는 '아이유'가 직접 참여하여 또 한 번 멋진 호흡을 자랑했다. 지난달 정규앨범의 첫 번째 선공개곡으로 발표되어 '아이유 표 발라드' 특유의 섬세한 감성으로 오랜 시간 리스너들의 큰 사랑을 받아오고 있다.</div><div>	&nbsp;</div><div>	09. 그렇게 사랑은</div><div>	Composed by 이병우 / Lyrics by 이병우 / Arranged by 이병우</div><div>	기타의 첫 3음만으로 아티스트 '이병우'의 내공을 들을 수 있는 클래식한 느낌의 발라드이다. 단지 기타 한 대와 목소리 하나로 5분 가까이 되는 러닝타임을 긴장감 있게 끌고 가는 두 아티스트의 대화가 근사하다. 실제 매번 원테이크로 서로 호흡하며 녹음한 노력이 그대로 전해진다. 이번 앨범에서는 유일하게 '아이유'가 작사에 참여하지 않은 곡으로 작곡, 작사, 연주에 모두 '이병우'가 나섰다.</div><div>	&nbsp;</div><div>	10. 이름에게 *TITLE</div><div>	Composed by 이종훈 / Lyrics by 아이유, 김이나 / Arranged by 이종훈, 홍소진&nbsp;</div><div>	길이와 구성 모두 이번 앨범에서 가장 큰 사이즈를 자랑하며 더블 타이틀곡으로 낙점이 된 이 곡은 흡사 '아이유'의 정규2집 1번 트랙 \"비밀\"이란 곡을 떠올리게 할 만큼 웅장한 사운드가 돋보이는 팝발라드 트랙이다. 우리나라 독보적인 스트링 편곡자 '박인영'의 지휘 아래 펼쳐지는 아름다운 스트링 선율과, '아이유'의 콘서트에서 늘 환상의 호흡을 보여주는, 이른바 '아이유밴드' 멤버들이 라이브로 공연하듯 합주하며 가감 없이 실력 발휘를 하였으며, 그 틈으로 단 하나의 코러스도 없이 그 거대한 사운드를 뚫고 나오는 '아이유'의 목소리까지. 그 한 줄기 목소리가 전하는 위로는 어디에라도 닿을 듯이 기세 있다. 작곡에는 '이종훈', 작사는 '아이유'와 '김이나'가 처음으로 공동 작업을 했다.</div></div>"

# 트랙 check
# 트랙, 제목, 아티스트, 디스크넘버, 타이틀
OutputTo "track"
SayOutput "tTrack"
OutputTo "tracks"
SayOutput "tTracks"
OutputTo "ARTIST"
SayOutput "tArtist"
OutputTo "TrackTitle"
SayOutput "tTrackTitle"
OutputTo "CD"
SayOutput "tCD"

# drop temporary variables
set "tTrack"
set "tTracks"
set "tArtist"
set "tCD"
set "tTrackTitle"