#pragma mark - Selector func
//- (void)loadStateDidChange:(NSNotification*)notification {
//    IJKMPMovieLoadState loadState = _player.loadState;
//    if ((loadState & IJKMPMovieLoadStatePlaythroughOK) != 0) {
//        NSLog(@"LoadStateDidChange: IJKMovieLoadStatePlayThroughOK: %d\n",(int)loadState);
//    }else if ((loadState & IJKMPMovieLoadStateStalled) != 0) {
//        NSLog(@"loadStateDidChange: IJKMPMovieLoadStateStalled: %d\n", (int)loadState);
//    } else {
//        NSLog(@"loadStateDidChange: ???: %d\n", (int)loadState);
//    }
//}
//
//- (void)moviePlayBackFinish:(NSNotification*)notification {
//    int reason =[[[notification userInfo] valueForKey:IJKMPMoviePlayerPlaybackDidFinishReasonUserInfoKey] intValue];
//    switch (reason) {
//        case IJKMPMovieFinishReasonPlaybackEnded:
//            NSLog(@"playbackStateDidChange: IJKMPMovieFinishReasonPlaybackEnded: %d\n", reason);
//            break;
//            
//        case IJKMPMovieFinishReasonUserExited:
//            NSLog(@"playbackStateDidChange: IJKMPMovieFinishReasonUserExited: %d\n", reason);
//            break;
//            
//        case IJKMPMovieFinishReasonPlaybackError:
//            NSLog(@"playbackStateDidChange: IJKMPMovieFinishReasonPlaybackError: %d\n", reason);
//            break;
//            
//        default:
//            NSLog(@"playbackPlayBackDidFinish: ???: %d\n", reason);
//            break;
//    }
//}
//
//- (void)mediaIsPreparedToPlayDidChange:(NSNotification*)notification {
//    NSLog(@"mediaIsPrepareToPlayDidChange\n");
//}
//
//- (void)moviePlayBackStateDidChange:(NSNotification*)notification {
//    switch (_VideoPlayer.playbackState) {
//        case IJKMPMoviePlaybackStateStopped:
//            NSLog(@"IJKMPMoviePlayBackStateDidChange %d: stoped", (int)_player.playbackState);
//            break;
//            
//        case IJKMPMoviePlaybackStatePlaying:
//            NSLog(@"IJKMPMoviePlayBackStateDidChange %d: playing", (int)_player.playbackState);
//            break;
//            
//        case IJKMPMoviePlaybackStatePaused:
//            NSLog(@"IJKMPMoviePlayBackStateDidChange %d: paused", (int)_player.playbackState);
//            break;
//            
//        case IJKMPMoviePlaybackStateInterrupted:
//            NSLog(@"IJKMPMoviePlayBackStateDidChange %d: interrupted", (int)_player.playbackState);
//            break;
//            
//        case IJKMPMoviePlaybackStateSeekingForward:
//        case IJKMPMoviePlaybackStateSeekingBackward: {
//            NSLog(@"IJKMPMoviePlayBackStateDidChange %d: seeking", (int)_player.playbackState);
//            break;
//        }
//            
//        default: {
//            NSLog(@"IJKMPMoviePlayBackStateDidChange %d: unknown", (int)_player.playbackState);
//            break;
//        }
//    }
//}
//
//#pragma Install Notifiacation
//- (void)installMovieNotificationObservers {
//    [[NSNotificationCenter defaultCenter] addObserver:self
//                                             selector:@selector(loadStateDidChange:)
//                                                 name:IJKMPMoviePlayerLoadStateDidChangeNotification
//                                               object:_player];
//    [[NSNotificationCenter defaultCenter] addObserver:self
//                                             selector:@selector(moviePlayBackFinish:)
//                                                 name:IJKMPMoviePlayerPlaybackDidFinishNotification
//                                               object:_player];
//    
//    [[NSNotificationCenter defaultCenter] addObserver:self
//                                             selector:@selector(mediaIsPreparedToPlayDidChange:)
//                                                 name:IJKMPMediaPlaybackIsPreparedToPlayDidChangeNotification
//                                               object:_player];
//    
//    [[NSNotificationCenter defaultCenter] addObserver:self
//                                             selector:@selector(moviePlayBackStateDidChange:)
//                                                 name:IJKMPMoviePlayerPlaybackStateDidChangeNotification
//                                               object:_player];
//}
//
//- (void)removeMovieNotificationObservers {
//    [[NSNotificationCenter defaultCenter] removeObserver:self
//                                                    name:IJKMPMoviePlayerLoadStateDidChangeNotification
//                                                  object:_player];
//    [[NSNotificationCenter defaultCenter] removeObserver:self
//                                                    name:IJKMPMoviePlayerPlaybackDidFinishNotification
//                                                  object:_player];
//    [[NSNotificationCenter defaultCenter] removeObserver:self
//                                                    name:IJKMPMediaPlaybackIsPreparedToPlayDidChangeNotification
//                                                  object:_player];
//    [[NSNotificationCenter defaultCenter] removeObserver:self
//                                                    name:IJKMPMoviePlayerPlaybackStateDidChangeNotification
//                                                  object:_player];
//}
